#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <memory>
#include "Collection.h"

class Editor {
    private: 
        std::vector<std::shared_ptr<Collection>>& collections;

    public:
        Editor(std::vector<std::shared_ptr<Collection>>& cls) : collections(cls) {};
        ~Editor() = default;
        void editNote(Note& note) const;
        void deleteNote(Note& note) const;
};

void Editor::editNote(Note& note) const {
    if(note.isLocked())
        return;
    
    std::cout << "Enter text. Type 'END' on a new line to finish: \n";

    std::string noteContent;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        if (line == "END") {
            break;
        }
        noteContent += line + "\n";
    }

    if(noteContent != std::string("END")){
        note.setText(noteContent);
    }

    std::string newTitle;
    std::cout << "Enter a new title or type END: ";
    std::getline(std::cin, newTitle);

    if(newTitle != std::string("END")){
        note.setTitle(newTitle);
    }
}

void Editor::deleteNote(Note& note) const {
    if(note.isLocked())
        return;

    for(auto c: collections) {
            c->removeNote(note);
        }

    note.~Note();
}

#endif