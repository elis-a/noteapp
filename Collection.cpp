//
// Created by elisa on 18/06/2025.
//

#include "Collection.h"

Collection::Collection(const std::string &name) : name(name) {}

const std::string &Collection::getName() const {
    return name;
};

// Aggiunge una nota alla collezione, controllando prima che non sia già presente
void Collection::addNote(const std::shared_ptr<Note> &note) {
    if (std::find(notes.begin(), notes.end(), note) == notes.end()) {
        notes.push_back(note);
        notifyObservers();
    }
}

// Rimuove una nota dalla collezione cercandola tramite il titolo. Restituisce true o false se la cancellazione è andata a buon fine o meno
bool Collection::removeNote(const std::string &title) {
    auto it = std::remove_if(notes.begin(), notes.end(), [&](const std::shared_ptr<Note> &n) {
        return n->getTitle() == title;
    });

    if (it != notes.end()) {
        notes.erase(it, notes.end());
        notifyObservers();
        return true;
    }
    return false;
}

const std::vector<std::shared_ptr<Note>> &Collection::getNotes() const {
    return notes;
}

// Registra un nuovo observer
void Collection::attachObserver(Observer *observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

// Rimuove un observer
void Collection::detachObserver(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Invia una notifica a tutti gli observer registrati per informarli delle modifiche
void Collection::notifyObservers() const {
    for (auto *observer: observers) {
        observer->onCollectionChanged(*this, notes.size());
    }
}

// Cerca una nota all'interno della collezione tramite il titolo e, se la trova, ne restituisce un puntatore; altrimenti restituisce un nullptr
std::shared_ptr<Note> Collection::getNote(const std::string &title) const {
    for (const auto &note: notes) {
        if (note->getTitle() == title) {
            return note;
        }
    }
    return nullptr;
}
