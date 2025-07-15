#include <gtest/gtest.h>
#include "NoteManager.h"
#include "Note.h"

// Test di prova, sempre true
TEST(ManagerTest, Placeholder) {
    EXPECT_TRUE(true);
}

// Verifica della creazione di una collection
TEST(NoteManagerTest, CreateAndGetCollection) {
    NoteManager manager;
    manager.createCollection("Personal");

    ASSERT_TRUE(manager.hasCollection("Personal"));

    auto collection = manager.getCollection("Personal");

    ASSERT_NE(collection, nullptr);
    ASSERT_EQ(collection->getName(), "Personal");
}

// Verifica della creazione di una collection duplicata
TEST(NoteManagerTest, CreateDuplicateCollection) {
    NoteManager manager;
    manager.createCollection("Work");

    ASSERT_THROW(manager.createCollection("Work"), std::runtime_error);
}

// Verifica della cancellazione di una collection
TEST(NoteManagerTest, DeleteCollection) {
    NoteManager manager;
    manager.createCollection("ToDelete");

    ASSERT_TRUE(manager.hasCollection("ToDelete"));

    manager.deleteCollection("ToDelete");

    ASSERT_FALSE(manager.hasCollection("ToDelete"));
}

// Verifica della cancellazione di una collection inesistente
TEST(NoteManagerTest, DeleteNonExistentCollection) {
    NoteManager manager;

    ASSERT_THROW(manager.deleteCollection("NonExistent"), std::runtime_error);
}

// Verifica dei nomi delle collection
TEST(NoteManagerTest, ListCollectionNames) {
    NoteManager manager;
    manager.createCollection("First");
    manager.createCollection("Second");
    manager.createCollection("Third");

    auto names = manager.listCollectionNames();

    ASSERT_EQ(names.size(), 3);

    bool foundFirst = std::find(names.begin(), names.end(), "First") != names.end();
    bool foundSecond = std::find(names.begin(), names.end(), "Second") != names.end();
    bool foundThird = std::find(names.begin(), names.end(), "Third") != names.end();

    ASSERT_TRUE(foundFirst);
    ASSERT_TRUE(foundSecond);
    ASSERT_TRUE(foundThird);
}
