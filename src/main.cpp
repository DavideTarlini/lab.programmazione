#include "Note.h"
#include "Collection.h"
#include "Editor.h"

int main(){
    /*auto e = new Editor();
    auto wc = e->addCollection(std::string("coll"));

    auto n1 = e->createNote(std::string("Note 1"));
    std::cout << n1.use_count() << std::endl;
    e->addNoteToCollection(n1.lock(), std::string("coll"));
    
    e->removeNotefromCollection(n1.lock(), std::string("coll"));
    std::cout << n1.use_count() << std::endl;
    e->deleteNote(n1.lock());
    std::cout << n1.use_count() << std::endl;

    e->removeCollection(wc.lock());*/

    /*auto e = new Editor();
    auto wn = e->createNote(std::string("note"));
    auto wn_name = wn.lock()->getName();
    auto coll = e->addCollection(std::string("coll"));
    e->addNoteToCollection(wn_name, std::string("coll"));

    e->removeNotefromCollection(wn_name, std::string("inexistent collection"));
    int i = wn.lock()->numOfCollections();
    e->removeNotefromCollection(wn_name, std::string("coll"));
    i = wn.lock()->numOfCollections();*/

    return 0;
}