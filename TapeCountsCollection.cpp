//
// Created by Maria on 13.05.2024.
//

#include "TapeCountsCollection.h"

void TapeCountsCollection::increment(const int &value) {
    moveTo(value + OFFSET);
    int oldCount = counts_->read();
    counts_->write(oldCount + 1);
}

size_t TapeCountsCollection::get(const int &value) const {
    moveTo(value + OFFSET);
    return counts_->read();
}

TapeCountsCollection::TapeCountsCollection(TapeCountsCollection::tape_ptr tape) :
        counts_(std::move(tape)) {}

void TapeCountsCollection::moveTo(int position) const {
    if (std::abs(static_cast<int>(position - counts_->index())) <= position) {
        if (counts_->index() > position) {
            while (counts_->index() != position) {
                counts_->moveBack();
            }
            return;
        }
        moveForwardToPosition(position);
        return;
    }
    counts_->rewind();
    moveForwardToPosition(position);
}

void TapeCountsCollection::moveForwardToPosition(int position) const {
    while (counts_->index() != position) {
        counts_->moveForward();
    }
}

void TapeCountsCollection::reset() {
    size_t initialIndex = counts_->index();
    while (counts_->index() < counts_->length()) {
        counts_->write(0);
        counts_->moveForward();
    }
    if (initialIndex > 0) {
        counts_->rewind();
        while (counts_->index() < initialIndex) {
            counts_->write(0);
            counts_->moveForward();
        }
    }
}