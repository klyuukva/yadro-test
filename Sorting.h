//
// Created by Maria on 13.05.2024.
//

#ifndef YADRO_TEST_SORTING_H
#define YADRO_TEST_SORTING_H


#include "tape.h"

class Sorting {
public:
    void operator()(Tape& inputTape, Tape& outputTape, const size_t& memoryLimit, const Delays& delays);
private:
    static const std::string TEMP_DIRECTORY_NAME;
    static const std::string COUNTS_TAPE_FILENAME;
    static const std::string TEMP_TAPE_FILENAME;
    static int nthDigit(int32_t value, size_t n);
};


#endif //YADRO_TEST_SORTING_H
