//
// Created by Maria on 13.05.2024.
//

#ifndef YADRO_TEST_TAPECOUNTSCOLLECTION_H
#define YADRO_TEST_TAPECOUNTSCOLLECTION_H


#include <memory>
#include "tape.h"
#include "CountsCollection.h"

class TapeCountsCollection : public CountsCollection {
public:
    using tape_ptr = std::unique_ptr<Tape>;
    explicit TapeCountsCollection(tape_ptr tape);
    void increment(const int& value) override;
    size_t get(const int& value) const override;
    void reset() override;
private:
    tape_ptr counts_;
    void moveTo(int position) const;
    void moveForwardToPosition(int position) const;
};


#endif //YADRO_TEST_TAPECOUNTSCOLLECTION_H
