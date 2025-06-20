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

    void showMenu() const;
    void handleUserInput(int choice);
    void createCollection();
    void listCollections();
    void createNote();
    void toggleNoteImportant();
    void toggleNoteLock();
    void deleteCollection();
};


#endif //NOTES_1_NOTEAPP_H
