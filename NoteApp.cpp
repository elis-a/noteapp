//
// Created by elisa on 20/06/2025.
//

#include "NoteApp.h"
#include <iostream>

NoteApp::NoteApp() : observer(std::make_shared<CollectionObserver>()) {}

void NoteApp::run() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleUserInput(choice);
    } while (choice != 0);
}

void NoteApp::showMenu() const {
    std::cout << "\n--- Note Manager ---\n";
    std::cout << "1. Create collection\n";
    std::cout << "2. List collections\n";
    std::cout << "3. Create note\n";
    std::cout << "4. Toggle note importance\n";
    std::cout << "5. Toggle note lock\n";
    std::cout << "6. Delete collection\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

void NoteApp::handleUserInput(int choice) {
    switch (choice) {
        case 1: createCollection(); break;
        case 2: listCollections(); break;
        case 3: createNote(); break;
        case 4: toggleNoteImportant(); break;
        case 5: toggleNoteLock(); break;
        case 6: deleteCollection(); break;
        case 0: std::cout << "Exiting...\n"; break;
        default: std::cout << "Invalid choice.\n";
    }
}

void NoteApp::createCollection() {
    std::string name;
    std::cout << "Collection name: ";
    std::getline(std::cin, name);
    try {
        manager.createCollection(name);
        auto collection = manager.getCollection(name);
        collection->attachObserver(observer.get());
        std::cout << "Collection \"" << name << "\" created.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

void NoteApp::listCollections() {
    auto names = manager.listCollectionNames();
    if (names.empty()) {
        std::cout << "No collections found.\n";
    } else {
        std::cout << "Collections:\n";
        for (const auto& name : names) {
            std::cout << "- " << name << '\n';
        }
    }
}

void NoteApp::createNote() {
    std::string title, text, collectionName;
    std::cout << "Note Title: ";
    std::getline(std::cin, title);
    std::cout << "Note text: ";
    std::getline(std::cin, text);

    std::cout << "Collection name: ";
    std::getline(std::cin, collectionName);

    if (!manager.hasCollection(collectionName)){
        std::cout << "Collection doesn't exist. \n";
        return;
    }

    auto note = std::make_shared<Note>(title, text);
    try {
        auto collection = manager.getCollection(collectionName);
        collection->addNote(note);
        std::cout << "Note added to collection. \n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

void NoteApp::toggleNoteImportant() {
    std::string title;
    std::cout << "Note title: ";
    std::getline(std::cin, title);

    auto note = manager.findNoteInAllCollection(title);
    if (note) {
        note->toggleImportant();
        std::cout << "Toggled importance. \n";
    } else {
        std::cout << "Note not found. \n";
    }
}

void NoteApp::toggleNoteLock() {
    std::string title;
    std::cout << "Note title: ";
    std::getline(std::cin, title);

    auto note = manager.findNoteInAllCollection(title);
    if (note) {
        note->toggleLock();
        std::cout << "Toggles lock status. \n";
    } else {
        std::cout << "Note not found. \n";
    }
}

void NoteApp::deleteCollection() {
    std::string name;
    std::cout << "Collection name: ";
    std::getline(std::cin, name);
    try {
        manager.deleteCollection(name);
        std::cout << "Collection deleted. \n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}


