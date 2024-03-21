#include <memory>
#include "Collection.h"
#include "Note.h"
#include "Editor.h"
#include <iostream>


int main(){
    auto e = new Editor();
    auto wc = e->addCollection(std::string("coll"));

    auto n1 = e->createNote(std::string("Note 1"));
    std::cout << n1.use_count() << std::endl;
    e->addNoteToCollection(n1.lock(), std::string("coll"));
    
    e->removeNotefromCollection(n1.lock(), std::string("coll"));
    std::cout << n1.use_count() << std::endl;
    e->deleteNote(n1.lock());
    std::cout << n1.use_count() << std::endl;

    e->removeCollection(wc.lock());

    return 0;
}