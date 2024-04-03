#include <gtest/gtest.h>

#include "../src/Collection.h"
#include "../src/CollectionObserver.h"
#include "../src/Note.h"
#include "../src/ImportantCollection.h"

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

TEST(CollectionTest, attach){
    auto obs = std::make_shared<CollectionObserver>();
    auto coll = std::make_shared<Collection>(std::string("coll"));

    coll->attach(obs);
    ASSERT_EQ(1, coll->numOfObservers());
}

TEST(CollectionTest, detach){
    auto obs_1 = std::make_shared<CollectionObserver>();
    auto obs_2 = std::make_shared<CollectionObserver>();
    auto coll = std::make_shared<Collection>(std::string("coll"));

    coll->attach(obs_1);
    coll->detach(obs_2);
    ASSERT_EQ(1, coll->numOfObservers());

    coll->detach(obs_1);
    ASSERT_EQ(0, coll->numOfObservers());
}

TEST(CollectionTest, addNote){
    auto n = std::make_shared<Note>(std::string("note"), std::string("text"));
    auto coll_1 = std::make_shared<Collection>(std::string("coll"));
    auto coll_2 = std::make_shared<Collection>(std::string("coll"));
    auto imp_coll = std::make_shared<ImportantCollection>();

    coll_1->addNote(n);
    auto addedNote = coll_1->getNote(std::string("note"));
    auto n_added = n->inCollection();
    ASSERT_EQ(true, n_added);
    ASSERT_EQ(n.get(), addedNote.lock().get());

    coll_2->addNote(n);
    addedNote = coll_2->getNote(std::string("note"));
    ASSERT_EQ(nullptr, addedNote.lock().get());

    imp_coll->addNote(n);
    addedNote = imp_coll->getNote(std::string("note"));
    ASSERT_EQ(n.get(), addedNote.lock().get());
}

TEST(CollectionTest, removeNote){
    auto n = std::make_shared<Note>(std::string("note"), std::string("text"));
    auto coll = std::make_shared<Collection>(std::string("coll"));
    auto o = std::make_shared<CollectionObserver>();

    coll->attach(o);
    coll->addNote(n);
    coll->getNote(std::string("note"));
    coll->removeNote(n);
    ASSERT_EQ(0, o->getObservedSize());
}