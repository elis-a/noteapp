//
// Created by elisa on 18/06/2025.
//

#include "NoteManager.h"
#include <algorithm>
#include <stdexcept>

void NoteManager::createCollection(const std::string& name) {
    if (collections.find(name) != collections.end()) {
        throw std::runtime_error("Collection with this name already exists.");
    }
    collections[name] = std::make_shared<Collection>(name);
}

void NoteManager::deleteCollection(const std::string &name) {
    auto it = collections.find(name);
    if (it != collections.end()) {
        collections.erase(it);
    } else {
        throw std::runtime_error("Collection not found.");
    }
}

std::shared_ptr<Collection> NoteManager::getCollection(const std::string& name) const {
    auto it = collections.find(name);
    if(it != collections.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Collection not found.");
    }
}

bool NoteManager::hasCollection(const std::string& name) const {
    return collections.find(name) != collections.end();
}

std::vector<std::string> NoteManager::listCollectionNames() const {
    std::vector<std::string> names;
    for (const auto& pair : collections) {
        names.push_back(pair.first);
    }
    return names;
}

std::shared_ptr<Note> NoteManager::findNoteInAllCollection(const std::string& title) const {
    for (const auto& pair : collections) {
        const std::string& name = pair.first;
        const std::shared_ptr<Collection>& collection = pair.second;

        auto note = collection->findNoteByTitle(title);
        if (note != nullptr) {
            return note;
        }
    }
    return nullptr;
}





