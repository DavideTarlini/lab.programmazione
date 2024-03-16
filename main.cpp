#include <memory>
#include "CollectionObserver.h"
#include "Collection.h"
#include "Note.h"
#include "Editor.h"


int main(){
    auto e = new Editor();
    auto wc = e->addCollection(std::string("coll"));
    auto wo = e->addObserverToCollection(wc);

    auto n1 = e->createNote(std::string("Note 1"));
    std::cout << n1.use_count() << std::endl;
    e->addNoteToCollection(n1, std::string("coll"));
    
    e->removeNotefromCollection(n1, std::string("coll"));
    std::cout << n1.use_count() << std::endl;
    e->deleteNote(n1);
    std::cout << n1.use_count() << std::endl;

    //e->removeCollection(wc.lock());
    e->removeObserverToCollection(wo, wc);

    return 0;
}