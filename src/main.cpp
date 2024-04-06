#include "Note.h"
#include "Collection.h"
#include "CollectionObserver.h"

int main(){
    auto coll = std::make_shared<Collection>(std::string("coll"), false);
    auto obs = new CollectionObserver(coll);
    
    delete obs;
    

    return 0;
}