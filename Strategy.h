#ifndef STRATEGY_H
#define STRATEGY_H

#include "Note.h"

class Strategy {
    public:
        virtual void execute(Note& note) const = 0;

    protected:
        Strategy() = default;
        ~Strategy() = default;
};

#endif