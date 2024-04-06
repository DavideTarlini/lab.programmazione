#include "Note.h"
#include "Collection.h"
#include "CollectionObserver.h"

int main(){
    auto coll = new Collection(std::string("coll"), false);
    auto obs = new CollectionObserver(coll);
    
    delete obs;
    delete coll;
    

    return 0;
}