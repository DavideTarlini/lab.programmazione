#ifndef EDITNOTESTRATEGY_H
#define EDITNOTESTRATEGY_H

#include "Strategy.h"
#include <string>
#include <iostream>

class EditNoteStrategy : public Strategy {
public:
    EditNoteStrategy() = default;
    ~EditNoteStrategy() = default;
    void execute(Note& note) const override;
};

void EditNoteStrategy::execute(Note& note) const {
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

#endif