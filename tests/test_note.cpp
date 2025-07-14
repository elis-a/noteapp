#include <gtest/gtest.h>
#include "Note.h"

// test di prova, sempre true
TEST(NoteTest, Placeholder) {
    EXPECT_TRUE(true);
}

// verifica del costruttore e dei getter della funzione
TEST(NoteTest, ConstructorAndGetters) {
    Note note("Test Title", "This is a test note.");

    ASSERT_EQ(note.getTitle(), "Test Title");
    ASSERT_EQ(note.getText(), "This is a test note.");

    ASSERT_FALSE(note.isLocked());
    ASSERT_FALSE(note.isImportant());
}

// verifica della modifica del text
TEST(NoteTest, SetText) {
    Note note("Test Title", "Initial text.");
    note.setText("Updated text.");

    ASSERT_EQ(note.getText(), "Updated text.");
}

// verifica toggle locked
TEST(NotesTest, ToggleLock) {
    Note note("Test Title", "Some text.");

    ASSERT_FALSE(note.isLocked());

    note.toggleLock();
    ASSERT_TRUE(note.isLocked());

    note.toggleLock();
    ASSERT_FALSE(note.isLocked());
}

// verifica toggle important
TEST(NoteTest, ToggleImportant) {
    Note note("Test title", "Some text.");

    ASSERT_FALSE(note.isImportant());

    note.toggleImportant();
    ASSERT_TRUE(note.isImportant());

    note.toggleImportant();
    ASSERT_FALSE(note.isImportant());
}




