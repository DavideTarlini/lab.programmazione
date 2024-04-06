#include <gtest/gtest.h>

#include "../src/Collection.h"
#include "../src/CollectionObserver.h"
#include "../src/Note.h"

TEST(NoteTest, edit){
    auto note = new Note(std::string("note"), std::string("text"));
    
    note->lock();
    note->setName(std::string("new name"));
    note->setText(std::string("new text"));
    ASSERT_EQ(std::string("note"), note->getName());
    ASSERT_EQ(std::string("text"), note->getText());

    note->unlock();
    note->setName(std::string("new name"));
    note->setText(std::string("new text"));
    ASSERT_EQ(std::string("new name"), note->getName());
    ASSERT_EQ(std::string("new text"), note->getText());
}

TEST(CollectionObserverTest, attach){
    auto coll = new Collection(std::string("coll"), false);
    auto obs = new CollectionObserver(coll);

    ASSERT_EQ(1, coll->numOfObservers());

    delete obs;
    delete coll;
}

TEST(CollectionObserverTest, detach){
    auto coll = new Collection(std::string("coll"), false);
    auto obs = new CollectionObserver(coll);

    delete obs;
    ASSERT_EQ(0, coll->numOfObservers());

    delete coll;
}

TEST(CollectionTest, addNote){
    auto n = std::make_shared<Note>(std::string("note"), std::string("text"));
    auto coll_1 = new Collection(std::string("coll"), false);
    auto coll_2 = new Collection(std::string("coll"), false);
    auto imp_coll = new Collection(std::string("coll"), true);
    auto obs_1 = new CollectionObserver(coll_1);
    auto obs_2 = new CollectionObserver(coll_2);
    auto obs_imp = new CollectionObserver(imp_coll);

    coll_1->addNote(n);
    auto addedNote = coll_1->getNote(std::string("note"));
    auto n_added = n->inCollection();
    ASSERT_EQ(true, n_added);
    ASSERT_EQ(1, obs_1->getObservedSize());
    ASSERT_EQ(n.get(), addedNote.lock().get());

    coll_2->addNote(n);
    addedNote = coll_2->getNote(std::string("note"));
    ASSERT_EQ(0, obs_2->getObservedSize());
    ASSERT_EQ(nullptr, addedNote.lock().get());

    imp_coll->addNote(n);
    addedNote = imp_coll->getNote(std::string("note"));
    ASSERT_EQ(1, obs_imp->getObservedSize());
    ASSERT_EQ(n.get(), addedNote.lock().get());

    delete obs_1;
    delete obs_2;
    delete obs_imp;
    delete coll_1;
    delete coll_2;
    delete imp_coll;
}

TEST(CollectionTest, removeNote){
    auto n = std::make_shared<Note>(std::string("note"), std::string("text"));
    auto coll = new Collection(std::string("coll"), false);
    auto o = new CollectionObserver(coll);

    coll->addNote(n);
    coll->getNote(std::string("note"));
    coll->removeNote(n);
    ASSERT_EQ(0, o->getObservedSize());

    delete o;
    delete coll;
}