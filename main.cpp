#include <memory>
#include "CollectionObserver.h"
#include "Collection.h"
#include "Note.h"
#include "Editor.h"


int main(){
    auto n1 = Note(std::string("Note 1"), std::string("aaaaa"));
    auto n2 = new Note(std::string("Note 2"), std::string("bbbbb"));
    auto n3 = Note(std::string("Note 3"), std::string("ccccc"));

    auto obs = new CollectionObserver();
    auto coll1 = std::make_shared<Collection>(Collection(std::string("collection 1")));
    std::vector<std::shared_ptr<Collection>> collections;

    auto editor = new Editor(collections);

    try {
        collections.push_back(coll1);

        coll1->subscribe(*obs);
        coll1->addNote(n1);
        coll1->addNote(*n2);
        coll1->addNote(n3);
        //coll1->removeNote(n1);
        //coll1->removeNote(n2);
        //coll1->removeNote(n3);
        editor->deleteNote(n1);
        editor->deleteNote(*n2);
        editor->deleteNote(n3);
        coll1->addNote(n1);

        //std::cout << n1.getText() << std::endl;
        
        //editor->editNote(n1);

        //std::cout << n1.getText() << std::endl;

        coll1->addNote(*n2);
        editor->deleteNote(*n2);
        int i = 0;
        
        if(n2 == nullptr){
            std::cout << "hdhjsjsssjg" << std::endl;
        }
    }
    catch(const std::exception& e) {
        coll1->~Collection();
        obs->~CollectionObserver();
        editor->~Editor();
    }

    return 0;
}