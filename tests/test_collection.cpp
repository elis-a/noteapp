#include <gtest/gtest.h>
#include "Collection.h"
#include "Note.h"
#include "Observer.h"

// test di prova, sempre true
TEST(CollectionTest, Placeholder) {
    EXPECT_TRUE(true);
}

// "mock" observer per verificare che le notifiche vengano inviate
class MockObserver : public Observer {
public:
    int updateCount = 0;
    std::string lastCollectionName;
    size_t lastSize = 0;

    void onCollectionChanged(const Collection& collection, std::size_t newSize) override {
        updateCount++;
        lastCollectionName = collection.getName();
        lastSize = newSize;
    }
};

// verifica costruttore e nome della collection
TEST(CollectionTest, Constructor) {
    Collection collection("My Notes");
    ASSERT_EQ(collection.getName(), "My Notes");
    ASSERT_EQ(collection.getNotes().size(), 0);
}

// verifica dell'aggiunta di una nota
TEST(CollectionTest, AddNote) {
    Collection collection("Work");
    auto note = std::make_shared<Note>("Meeting", "Discuss project plan.");
    collection.addNote(note);

    ASSERT_EQ(collection.getNotes().size(), 1);
    ASSERT_EQ(collection.getNotes()[0]->getTitle(), "Meeting");
}

// verifica dell'aggiunta di una nota duplicata
TEST(CollectionTest, AddDuplicateNote) {
    Collection collection("Duplicates");
    auto note = std::make_shared<Note>("Unique Note", "Some text.");
    collection.addNote(note);
    collection.addNote(note);

    ASSERT_EQ(collection.getNotes().size(), 1);
}

// verifica della rimozione di una nota
TEST(CollectionTest, RemoveNote){
    Collection collection("To Delete");
    auto note = std::make_shared<Note>("Temporary", "This will be deleted.");
    collection.addNote(note);

    ASSERT_EQ(collection.getNotes().size(), 1);

    bool removed = collection.removeNote("Temporary");

    ASSERT_TRUE(removed);
    ASSERT_EQ(collection.getNotes().size(), 0);

    bool not_removed = collection.removeNote("NonExistent");

    ASSERT_FALSE(not_removed);
}

// verifica della ricerca di una nota
TEST(CollectionTest, GetNote) {
    Collection collection("Searching");
    auto note1 = std::make_shared<Note>("FindMe", "I'm here.");
    collection.addNote(note1);

    auto foundNote = collection.getNote("FindMe");

    ASSERT_NE(foundNote, nullptr);
    ASSERT_EQ(foundNote->getTitle(), "FindMe");

    auto notFoundNote = collection.getNote("Lost");

    ASSERT_EQ(notFoundNote, nullptr);
}

// verifica dell'observer e delle sue notifiche
TEST(CollectionTest, ObserverNotification) {
    Collection collection("Observed Collection");
    MockObserver observer;
    collection.attachObserver(&observer);

    ASSERT_EQ (observer.updateCount, 0);

    auto note = std::make_shared<Note>("Notify", "Trigger update.");
    collection.addNote(note);

    ASSERT_EQ(observer.updateCount, 1);
    ASSERT_EQ(observer.lastCollectionName, "Observed Collection");
    ASSERT_EQ(observer.lastSize, 1);

    collection.removeNote("Notify");

    ASSERT_EQ(observer.updateCount, 2);
    ASSERT_EQ(observer.lastSize, 0);

    collection.detachObserver(&observer);
    collection.addNote(note);

    ASSERT_EQ(observer.updateCount, 2);
}