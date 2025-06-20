//
// Created by elisa on 18/06/2025.
//

#include "Collection.h"

Collection::Collection(const std::string& name) : name(name) {}

const std::string& Collection::getName() const {
    return name;
};

void Collection::addNote(const std::shared_ptr<Note>& note) {
    if (std::find(notes.begin(), notes.end(), note) == notes.end()) {
        notes.push_back(note);
        note->setCollection(shared_from_this());
        notifyObservers();
    }
}

void Collection::removeNote(const std::shared_ptr<Note>& note) {
    auto it = std::remove(notes.begin(), notes.end(), note);
    if (it != notes.end()) {
        notes.erase(it, notes.end());
        note->setCollection(nullptr);
        notifyObservers();
    }
}

const std::vector<std::shared_ptr<Note>>& Collection::getNotes() const {
    return notes;
}

std::shared_ptr<Note> Collection::findNoteByTitle(const std::string& title) const {
    for (const auto& note : notes){
        if(note->getTitle() == title) {
            return note;
        }
    }
    return nullptr;
}

void Collection::attachObserver(Observer* observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

void Collection::detachObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Collection::notifyObservers() const {
    for (auto* observer : observers) {
        observer->onCollectionChanged(*this, notes.size());
    }
}