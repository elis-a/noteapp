//
// Created by elisa on 20/06/2025.
//

#ifndef NOTES_1_NOTEAPP_H
#define NOTES_1_NOTEAPP_H

#include "NoteManager.h"
#include "CollectionObserver.h"

class NoteApp {
public:
    NoteApp();
    void run();

private:
    NoteManager manager;
    std::shared_ptr<CollectionObserver> observer;

    void showMainMenu() const;
    void handleMainInput(int choice);
    void createCollection();
    void openCollection();
    void enterCollection(const std::string &name);
    void deleteCollection();
    void createNoteInCollection(const std::shared_ptr<Collection>&);
    void viewNote(const std::shared_ptr<Collection>&);
    void editNote(const std::shared_ptr<Collection>&);
    void deleteNote(const std::shared_ptr<Collection>&);
    void toggleNoteState(const std::shared_ptr<Collection>&);
    void viewImportantNotes();
};


#endif //NOTES_1_NOTEAPP_H
