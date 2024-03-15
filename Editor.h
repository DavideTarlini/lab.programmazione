#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "Strategy.h"
#include "DeleteNoteStrategy.h"
#include "Collection.h"

class Editor {
    private: 
        Strategy* strategy;
        std::vector<Collection> collections;

    public:
        Editor(std::vector<Collection> cls) : strategy(nullptr), collections(cls) {};
        ~Editor() = default;
        void setStrategy(Strategy* newStrategy);
        void edit(Note& note);
};

void Editor::setStrategy(Strategy* newStrategy) {
    strategy = newStrategy;
}

void Editor::edit(Note& note) {
    if(note.isLocked() || strategy == nullptr)
        return;

    if(typeid(strategy) == typeid(DeleteNoteStrategy*)) {
        for(auto c: collections) {
            c.removeNote(note);
        }
    }

    strategy->execute(note);
}

#endif