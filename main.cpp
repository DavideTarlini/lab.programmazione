#include "CollectionObserver.h"
#include "Collection.h"
#include "Note.h"
#include "Editor.h"
#include "EditNoteStrategy.h"


int main(){
    auto n1 = Note(std::string("Note 1"), std::string("aaaaa"));
    auto n2 = Note(std::string("Note 2"), std::string("bbbbb"));
    auto n3 = Note(std::string("Note 3"), std::string("ccccc"));

    auto obs = new CollectionObserver();
    auto coll1 = new Collection(std::string("collection 1"));
    std::vector<Collection> collections;

    auto editor = new Editor(collections);
    auto editText = new EditNoteStrategy();

    try {
        collections.push_back(*coll1);

        coll1->subscribe(*obs);
        coll1->addNote(n1);
        coll1->addNote(n2);
        coll1->addNote(n3);
        coll1->removeNote(n1);
        coll1->removeNote(n2);
        coll1->removeNote(n3);
        coll1->addNote(n1);

        std::cout << n1.getText() << std::endl;

        
        editor->setStrategy(editText);
        editor->edit(n1);

        std::cout << n1.getText() << std::endl;
    }
    catch(const std::exception& e) {
        coll1->~Collection();
        obs->~CollectionObserver();
        editor->~Editor();
        editText->~EditNoteStrategy();
    }

    return 0;
}