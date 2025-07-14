//
// Created by elisa on 18/06/2025.
//

#include "NoteManager.h"
#include <algorithm>
#include <stdexcept>

// Crea una nuova collezione di note, lanciando un'eccezione se esiste già una nota con quel nome
void NoteManager::createCollection(const std::string& name) {
    if (collections.find(name) != collections.end()) {
        throw std::runtime_error("Collection with this name already exists.");
    }
    collections[name] = std::make_shared<Collection>(name);
}

// Cerca una collezione tramite nome e se la trova la cancella. Se non esiste, lancia un'eccezione
void NoteManager::deleteCollection(const std::string &name) {
    auto it = collections.find(name);
    if (it != collections.end()) {
        collections.erase(it);
    } else {
        throw std::runtime_error("Collection not found.");
    }
}

// Cerca un'eccezione tramite nome lanciando un'eccezione se non la trova
std::shared_ptr<Collection> NoteManager::getCollection(const std::string& name) const {
    auto it = collections.find(name);
    if(it != collections.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Collection not found.");
    }
}

// Controlla se una collezione con un certo nome sia già presente nel gestore delle note
bool NoteManager::hasCollection(const std::string& name) const {
    return collections.find(name) != collections.end();
}

// Fornisce una lista con i nomi di tutte le collezioni
std::vector<std::string> NoteManager::listCollectionNames() const {
    std::vector<std::string> names;
    for (const auto& pair : collections) {
        names.push_back(pair.first);
    }
    return names;
}

// Cerca, tramite nome, una nota in tutte le collezioni. Restituisce la prima nota che corrisponde al titolo
std::shared_ptr<Note> NoteManager::findNoteInAllCollection(const std::string& title) const {
    for (const auto& pair : collections) {
        const std::string& name = pair.first;
        const std::shared_ptr<Collection>& collection = pair.second;

        auto note = collection->getNote(title);
        if (note != nullptr) {
            return note;
        }
    }
    return nullptr;
}