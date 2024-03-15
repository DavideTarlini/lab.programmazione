#ifndef DELETENOTESTRATEGY_H
#define DELETENOTESTRATEGY_H

#include <string>
#include <iostream>
#include "Note.h"
#include "Strategy.h"

class DeleteNoteStrategy : public Strategy {
public:
    DeleteNoteStrategy() = default;
    ~DeleteNoteStrategy() = default;
    void execute(Note& note) const override;
};

void DeleteNoteStrategy::execute(Note& note) const {
    note.~Note();
}

#endif