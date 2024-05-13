//
// Created by Maria on 13.05.2024.
//

#ifndef YADRO_TEST_VECTORCOUNTSCOLLECTION_H
#define YADRO_TEST_VECTORCOUNTSCOLLECTION_H

#include <vector>
#include "CountsCollection.h"

class VectorCountsCollection: public CountsCollection{
public:
    explicit VectorCountsCollection(const size_t& size);
    void increment(const int& value) override;
    size_t get(const int& value) const override;
    void reset() override;
private:
    std::vector<size_t> counts_;
};


#endif //YADRO_TEST_VECTORCOUNTSCOLLECTION_H
