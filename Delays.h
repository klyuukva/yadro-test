//
// Created by Maria on 13.05.2024.
//

#ifndef YADRO_TEST_DELAYS_H
#define YADRO_TEST_DELAYS_H
#include <iosfwd>

struct Delays {
    int move;
    int rewind;
    int write;
    int read;
    friend std::istream& operator>>(std::istream& is, Delays& obj);
};

#endif //YADRO_TEST_DELAYS_H
