//
// Created by elisa on 20/06/2025.
//

#include "NoteApp.h"
#include <iostream>
#include <limits>

NoteApp::NoteApp() : observer(std::make_shared<CollectionObserver>()) {
    manager.createCollection("Important");
}

// Avvia il ciclo principale dell'applicazione, che continua a mostrare il menu e gestisce le scelte dell'utente
// finché non sceglie di uscire dal programma
void NoteApp::run() {
    int choice;
    do {
        showMainMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        handleMainInput(choice);
    } while (choice != 0);
}

// Stampa a schermo il menu principale, mostrando le opzioni disponibili
void NoteApp::showMainMenu() const {
    std::cout << "\n--- Note Manager ---\n";
    std::cout << "1. Create collection\n";
    std::cout << "2. Open a collection\n";
    std::cout << "3. Delete a collection\n";
    std::cout << "4. View important notes\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

// Fa partire la funzione corretta in base all'input dell'utente
void NoteApp::handleMainInput(int choice) {
    switch (choice) {
        case 1:
            createCollection();
            break;
        case 2:
            openCollection();
            break;
        case 3:
            deleteCollection();
            break;
        case 4:
            viewImportantNotes();
            break;
        case 0:
            std::cout << "Exit...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
    }
}

// Guida l'utente nella creazione di una collezione chiedendo il nome che vuole dare alla collezione
void NoteApp::createCollection() {
    std::string name;
    std::cout << "Collection name: ";
    std::getline(std::cin, name);
    try {
        manager.createCollection(name);
        auto collection = manager.getCollection(name);
        collection->attachObserver(observer.get());
        std::cout << "Collection \"" << name << "\" created.\n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

// Chiede all'utente un input per decidere quale collezione aprire
void NoteApp::openCollection() {
    std::string name;
    std::cout << "Insert collection name:";
    std::getline(std::cin, name);
    enterCollection(name);
}

// Mostra il contenuto  di una collezione e un sotto-menu per interagire con le note al suo interno
void NoteApp::enterCollection(const std::string &name) {
    if (!manager.hasCollection(name)) {
        std::cout << "Collection not found\n";
        return;
    }

    auto collection = manager.getCollection(name);

    int choice;
    do {
        std::cout << "\n--- Collection: " << collection->getName() << " ---\n";
        const auto &notes = collection->getNotes();
        if (notes.empty()) {
            std::cout << "This collection is empty.\n";
        } else {
            for (const auto &note: collection->getNotes()) {
                std::cout << (note->isImportant() ? "[<3]" : "[  ]")
                          << (note->isLocked() ? "[L]" : "[ ]")
                          << " " << note->getTitle() << "\n";
            }
        }

        std::cout << "1. Add note\n";
        std::cout << "2. View note\n";
        std::cout << "3. Edit note\n";
        std::cout << "4. Delete note\n";
        std::cout << "5. Change note state (importance/lock)\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                createNoteInCollection(collection);
                break;
            case 2:
                viewNote(collection);
                break;
            case 3:
                editNote(collection);
                break;
            case 4:
                deleteNote(collection);
                break;
            case 5:
                toggleNoteState(collection);
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid choice. \n";
        }
    } while (choice != 0);
}

// Gestisce le cancellazioni delle collezioni, impedendo la cancellazione della collezione speciale "Important"
void NoteApp::deleteCollection() {
    std::string name;
    std::cout << "Collection name: ";
    std::getline(std::cin, name);

    if (name == "Important") {
        std::cout << "The 'Important' collection cannot be deleted.\n";
        return;
    }

    try {
        manager.deleteCollection(name);
        std::cout << "Collection deleted. \n";
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}

// Chiede all'utente titolo e testo della nuova nota da aggiungere alla collezione
void NoteApp::createNoteInCollection(const std::shared_ptr<Collection> &collection) {
    std::string title, text;
    std::cout << "Note title: ";
    std::getline(std::cin, title);
    std::cout << "Note text: ";
    std::getline(std::cin, text);

    auto note = std::make_shared<Note>(title, text);
    collection->addNote(note);
    std::cout << "Note added to collection.\n";
}

// Mostra i contenuti completi di una singola nota: titolo, testo e stati di blocco/importanza
void NoteApp::viewNote(const std::shared_ptr<Collection> &collection) {
    std::string title;
    std::cout << "Note title to view: ";
    std::getline(std::cin, title);

    auto note = collection->getNote(title);
    if (!note) {
        std::cout << "Note not found.\n";
        return;
    }

    std::cout << "\n--- Note: " << note->getTitle() << " ---\n";
    std::cout << "Important: " << (note->isImportant() ? "[<3]" : "[  ]") << "\n";
    std::cout << "Locked: " << (note->isLocked() ? "[L]" : "[ ]") << "\n";
    std::cout << "Text:\n" << note->getText() << "\n";
}

// Permette di modificare il testo di una nota, controllando prima che non sia bloccata
void NoteApp::editNote(const std::shared_ptr<Collection> &collection) {
    std::string title;
    std::cout << "Note title to edit: ";
    std::getline(std::cin, title);

    auto note = collection->getNote(title);
    if (!note) {
        std::cout << "Note not found.\n";
        return;
    }

    if (note->isLocked()) {
        std::cout << "Note is locked and cannot be edited.\n";
        return;
    }

    std::string newText;
    std::cout << "Enter new text: ";
    std::getline(std::cin, newText);
    note->setText(newText);
    std::cout << "Note updated.\n";
}

// Elimina una nota dalla collezione, controllando prima che non sia bloccata o importante
void NoteApp::deleteNote(const std::shared_ptr<Collection> &collection) {
    std::string title;
    std::cout << "Note title to delete: ";
    std::getline(std::cin, title);

    auto note = collection->getNote(title);

    if (!note) {
        std::cout << "Note not found.\n";
        return;
    } else if (note->isLocked()) {
        std::cout << "Note is locked and cannot be deleted.\n";
        return;
    } else if (note->isImportant()) {
        std::cout << "Note is important and cannot be deleted.\n";
        return;
    } else { collection->removeNote(title); }

}

// Permette di cambiare lo stato di importanza e di blocco di una nota
void NoteApp::toggleNoteState(const std::shared_ptr<Collection> &collection) {
    std::string title;
    std::cout << "Note title to change state: ";
    std::getline(std::cin, title);

    auto note = collection->getNote(title);
    if (!note) {
        std::cout << "Note not found.\n";
        return;
    }

    int choice;
    std::cout << "1. Toggle importance";
    std::cout << "\n 2. Toggle lock";
    std::cout << "\n Choice: ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        note->toggleImportant();
        auto importantCollection = manager.getCollection("Important");
        if (note->isImportant()) {
            importantCollection->addNote(note);
        } else {
            importantCollection->removeNote(note->getTitle());
        }
        std::cout << "Importance toggled.\n";
    } else if (choice == 2) {
        note->toggleLock();
        std::cout << "Lock status toggled.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

// Funzione che mostra la collezione speciale "Important"
void NoteApp::viewImportantNotes() {
    enterCollection("Important");
}
