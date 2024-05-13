//
// Created by Maria on 08.05.2024.
//

#ifndef YADRO_TEST_TAPE_ABSTRACT_H
#define YADRO_TEST_TAPE_ABSTRACT_H

#include <cstdio>

class TapeAbstract {
public:
    virtual size_t read() = 0;
    virtual void write(size_t value) = 0;
    virtual void moveForward() = 0;
    virtual void moveBack() = 0;
    virtual void rewind() = 0;
    virtual size_t length() = 0;
    virtual size_t index() = 0;
    virtual ~TapeAbstract() = default;
};
#endif //YADRO_TEST_TAPE_ABSTRACT_H
