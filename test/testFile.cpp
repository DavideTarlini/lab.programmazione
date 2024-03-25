#include <gtest/gtest.h>

#include "../src/Collection.h"
#include "../src/Note.h"
#include "../src/Editor.h"

TEST(NoteTest, attach){
auto note = new Note("note", "text");
    auto coll = std::make_shared<Collection>(std::string("coll"));

    note->attach(coll);
    ASSERT_EQ(1, note->numOfCollections());
}

TEST(NoteTest, detach){
    auto note = new Note("note", "text");
    auto coll = std::make_shared<Collection>(std::string("coll"));

    note->detach(coll);
    ASSERT_EQ(0, note->numOfCollections());

    note->attach(coll);
    note->detach(coll);
    ASSERT_EQ(0, note->numOfCollections());
}

TEST(NoteTest, removeCollections){
    auto note = new Note("note", "");
    auto coll_1 = std::make_shared<Collection>(std::string("coll_1"));
    auto coll_2 = std::make_shared<Collection>(std::string("coll_2"));
    auto coll_3 = std::make_shared<Collection>(std::string("coll_3"));
    auto coll_4 = std::make_shared<Collection>(std::string("coll_4"));

    note->attach(coll_1);
    note->attach(coll_2);
    note->attach(coll_3);
    note->attach(coll_4);
    note->removeCollections();
    ASSERT_FALSE(note->numOfCollections());
}

TEST(EditorTest, addCollection){
    auto e = new Editor();

    auto wc = e->addCollection(std::string("coll"));
    auto addedC = e->getCollection(std::string("coll"));

    ASSERT_EQ(1, e->numOfCollections());
    ASSERT_EQ(wc.lock()->getName(), addedC.lock()->getName());
}

TEST(EditorTest, removeCollection){
    auto e = new Editor();
    auto wc = e->addCollection(std::string("coll_1"));
    e->addCollection(std::string("coll_2"));

    e->removeCollection(std::string("wrong collection"));
    ASSERT_EQ(2, e->numOfCollections());

    e->removeCollection(wc.lock()->getName());    
    ASSERT_EQ(1, e->numOfCollections());

    auto remainingColl = e->getCollection(std::string("coll_2"));
    ASSERT_EQ(std::string("coll_2"), remainingColl.lock()->getName()); 
}

TEST(EditorTest, createNote){
    auto e = new Editor();

    auto wn = e->createNote(std::string("note"));
    auto n = e->getNote(std::string("note"));

    ASSERT_EQ(1, e->numOfNotes());
    ASSERT_EQ(wn.lock()->getName(), n.lock()->getName());
}

TEST(EditorTest, addNoteToCollection){
    auto e = new Editor();
    auto wn = e->createNote(std::string("note"));
    auto wn_name = wn.lock()->getName();
    auto coll = e->addCollection(std::string("coll"));

    e->addNoteToCollection(wn_name, std::string("inexistent collection"));
    ASSERT_EQ(0, wn.lock()->numOfCollections());
    ASSERT_EQ(0, coll.lock()->getSize());

    e->addNoteToCollection(wn_name, std::string("coll"));
    ASSERT_EQ(1, wn.lock()->numOfCollections());
    ASSERT_EQ(1, coll.lock()->getSize());
}

TEST(EditorTest, removeNotefromCollection){
    auto e = new Editor();
    auto wn = e->createNote(std::string("note"));
    auto wn_name = wn.lock()->getName();
    auto coll = e->addCollection(std::string("coll"));
    e->addNoteToCollection(wn_name, std::string("coll"));

    e->removeNotefromCollection(wn_name, std::string("inexistent collection"));
    ASSERT_EQ(1, wn.lock()->numOfCollections());
    ASSERT_EQ(1, coll.lock()->getSize());

    e->removeNotefromCollection(wn_name, std::string("coll"));
    ASSERT_EQ(0, wn.lock()->numOfCollections());
    ASSERT_EQ(0, coll.lock()->getSize());
}

TEST(EditorTest, editNoteName){
    auto e = new Editor();
    auto wn = e->createNote(std::string("note"));
    auto sn = wn.lock();

    e->editNoteName(sn->getName(), std::string("newName"));
    ASSERT_EQ(std::string("newName"), sn->getName());
    sn->lock();
    e->editNoteName(sn->getName(), std::string("anotherNewName"));
    ASSERT_EQ(std::string("newName"), sn->getName());
}

TEST(EditorTest, editNoteText){
    auto e = new Editor();
    auto wn = e->createNote(std::string("note"));
    auto sn = wn.lock();

    e->editNoteText(sn->getName(), std::string("newText, here"));
    ASSERT_EQ(std::string("newText, here"), sn->getText());
    sn->lock();
    e->editNoteText(sn->getName(), std::string("some other text"));
    ASSERT_EQ(std::string("newText, here"), sn->getText());
}

TEST(EditorTest, deleteNote){
    auto e = new Editor();
    auto wn = e->createNote(std::string("note_1"));
    e->createNote(std::string("note_2"));

    e->deleteNote(wn.lock()->getName());
    ASSERT_EQ(1, e->numOfNotes());
    auto remainingNote = e->getNote(std::string("note_2"));
    ASSERT_EQ(std::string("note_2"), remainingNote.lock()->getName());
}