//
// Created by Maria on 08.05.2024.
//


#include <fstream>
#include <thread>
#include <iterator>
#include "tape.h"


Tape::Tape(std::string filename, size_t length, const Delays &delays, Tape::Cond cond) :
        _tape_size(length),
        _index(0),
        _delays(delays),
        _filename(std::move(filename)) {
    switch (cond) {
        case Cond::OPEN_EXIST:
            openExist();
            break;
        case Cond::CREATE_OR_OVERWRITE:
            createOrOverwrite();
            break;
        case Cond::CREATE_IF_MISSING:
            createIfMiss();
            break;
    }
}

size_t Tape::read() {
    sleep(_delays.read);
    std::fstream file(_filename);
    if (!file) {
        file.close();
        throw std::runtime_error("error read file " + _filename);
    }
    int countOfElem = 0;
    int value = 0;
    while (countOfElem <= _index && countOfElem < _tape_size) {
        if (file.eof()) {
            file.close();
            throw std::runtime_error("file eof while");
        }
        file >> value >> std::ws;
        if (file.fail()) {
            file.close();
            throw std::runtime_error("file fail while");
        }
        ++countOfElem;
    }
    file >> std::ws;
    if (countOfElem == _tape_size && !file.eof()) {
        file.close();
        throw std::runtime_error("error count");
    }
    file.close();
    return value;
}

void Tape::write(size_t value) {
    sleep(_delays.write);
    std::vector<int> values(_tape_size);
    std::ifstream inFile(_filename);
    const std::string notOpenedMessage = "\"" + _filename + "\" not open for writing";
    if (!inFile) {
        inFile.close();
        throw std::runtime_error(notOpenedMessage);
    }
    int temp;
    int tempIndex = 0;
    while (!inFile.eof()) {
        inFile >> temp;
        if (inFile.fail() && !inFile.eof()) {
            inFile.close();
            throw std::runtime_error("not integers");
        }
        if (!inFile.eof()) {
            if (tempIndex >= _tape_size) {
                inFile.close();
                throw std::runtime_error("too many elements");
            }
            values[tempIndex] = temp;
            ++tempIndex;
        }
    }
    if (tempIndex < _tape_size) {
        inFile.close();
        throw std::runtime_error("not enough elements");
    }
    inFile.close();

    values[_index] = value;

    std::ofstream outFile(_filename, std::ios::trunc);
    if (!outFile) {
        inFile.close();
        throw std::runtime_error(notOpenedMessage);
    }
    std::ostream_iterator<int> outIterator(outFile, "\n");
    std::copy(values.begin(), values.end(), outIterator);
    outFile.close();
}

void Tape::sleep(int time) {
    std::this_thread::sleep_for(std::chrono::microseconds(time));
}

void Tape::moveForward() {
    if (_index == _tape_size) {
        throw std::out_of_range("Error with move forwarding");
    }
    sleep(_delays.move);
    ++_index;
}

void Tape::moveBack() {
    if (_index == 0) {
        throw std::out_of_range("Error with move back");
    }
    sleep(_delays.move);
    --_index;
}

void Tape::rewind() {
    sleep(_delays.rewind);
    _index = 0;
}

size_t Tape::length() {
    return _tape_size;
}

size_t Tape::index() {
    return _index;
}

void Tape::createIfMiss() {
    std::ifstream file(_filename);
    if (file) {
        throwIfEmpty(file);
        file.close();
        return;
    }
    createFile();
}

void Tape::createOrOverwrite() {
    std::ofstream  file(_filename, std::ios::trunc);
    if(!file) {
        file.close();
        throw std::runtime_error("cannot open or create file");
    }
    fillWithZeros(file);
    file.close();
}

void Tape::openExist() {
    std::ifstream file(_filename);
    if(file) {
        throwIfEmpty(file);
    } else {
        file.close();
        throw std::runtime_error("file " + _filename + " not open");
    }
}

void Tape::throwIfEmpty(std::ifstream &file) {
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        file.close();
        throw std::runtime_error("file " + _filename + " empty");
    }
}

void Tape::fillWithZeros(std::ofstream &newFile) const {
    for (size_t i = 0; i < _tape_size; ++i) {
        newFile << 0 << '\n';
    }
}

void Tape::createFile() {
    std::ofstream newFile(_filename);
    if (newFile) {
        fillWithZeros(newFile);
    } else {
        newFile.close();
        throw std::runtime_error("cannot create or open the file " + _filename);
    }
    newFile.close();
}
