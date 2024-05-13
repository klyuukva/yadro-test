//
// Created by Maria on 13.05.2024.
//

#include "Sorting.h"
#include "utils.h"
#include "CountsCollection.h"
#include "TapeCountsCollection.h"
#include "VectorCountsCollection.h"


const std::string Sorting::TEMP_DIRECTORY_NAME = "tmp";
const std::string Sorting::COUNTS_TAPE_FILENAME = TEMP_DIRECTORY_NAME + "/counts.txt";
const std::string Sorting::TEMP_TAPE_FILENAME = TEMP_DIRECTORY_NAME + "/temp.txt";
static const size_t BYTES_IN_INT32 = 4;
static const size_t COUNT_LENGTH = 19;
static const size_t MAX_DIGIT = 10;

void Sorting::operator()(Tape &inputTape, Tape &outputTape, const size_t &memoryLimit, const Delays &delays) {
    if(inputTape.length() != outputTape.length()) {
        throw std::invalid_argument("input and output tape length not match");
    }

    mkDirIfMiss(TEMP_DIRECTORY_NAME);

    std::unique_ptr<CountsCollection> counts;
    if (memoryLimit < COUNT_LENGTH * BYTES_IN_INT32) {
        counts = std::make_unique<TapeCountsCollection>(
                std::make_unique<Tape>(COUNTS_TAPE_FILENAME, COUNT_LENGTH, delays,
                                       Tape::Cond::CREATE_OR_OVERWRITE));
    } else {
        counts = std::make_unique<VectorCountsCollection>(COUNT_LENGTH);
    }

    Tape tempTape(TEMP_TAPE_FILENAME, inputTape.length(), delays, Tape::Cond::CREATE_OR_OVERWRITE);
    bool writeToTemp = true;
    Tape* readingTape = &inputTape;
    Tape* writingTape = &tempTape;
    for (size_t digitNumber = 0; digitNumber < MAX_DIGIT; ++digitNumber) {
        for (size_t i = 0; i < readingTape->length(); ++i) {
            int32_t value = readingTape->read();
            counts->increment(nthDigit(value, digitNumber));
            readingTape->moveForward();
        }
        readingTape->rewind();
        for (int i = 0; i < COUNT_LENGTH; ++i) {
            int occurrenceCounter = 0;
            while (occurrenceCounter < counts->get(i - CountsCollection::OFFSET)) {
                int32_t value = readingTape->read();
                if (nthDigit(value, digitNumber) == (i - CountsCollection::OFFSET)) {
                    writingTape->write(value);
                    writingTape->moveForward();
                    ++occurrenceCounter;
                }
                readingTape->moveForward();
            }
            if (readingTape->index() > 0) {
                readingTape->rewind();
            }
        }
        readingTape->rewind();
        writingTape->rewind();
        if (writeToTemp) {
            writeToTemp = false;
            readingTape = &tempTape;
            writingTape = &outputTape;
        } else {
            writeToTemp = true;
            readingTape = &outputTape;
            writingTape = &tempTape;
        }
        counts->reset();
    }
}

int Sorting::nthDigit(std::int32_t value, size_t n) {
    while (n > 0) {
        value /= 10;
        --n;
    }
    return value % 10;
}
