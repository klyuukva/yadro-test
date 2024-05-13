//
// Created by Maria on 13.05.2024.
//

#ifndef YADRO_TEST_COUNTSCOLLECTION_H
#define YADRO_TEST_COUNTSCOLLECTION_H

#include <cstddef>

class CountsCollection {
public:
    virtual ~CountsCollection() = default;
    static const int OFFSET = 9;
    virtual void increment(const int& value) = 0;
    virtual size_t get(const int& value) const = 0;
    virtual void reset() = 0;
};
#endif //YADRO_TEST_COUNTSCOLLECTION_H
