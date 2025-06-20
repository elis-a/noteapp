//
// Created by elisa on 18/06/2025.
//

#include "Note.h"
#include "Collection.h"

Note::Note(const std::string& title, const std::string& text) : title(title), text(text), locked(false), important(false) {}

const std::string& Note::getTitle() const {
    return title;
}

const std::string& Note::getText() const {
    return text;
}

bool Note::isLocked() const {
    return locked;
}

bool Note::isImportant() const {
    return important;
};

void Note::setText(const std::string& newText) {
    text = newText;
}

void Note::toggleLock() {
    locked = !locked;
}

void Note::toggleImportant() {
    important = !important;
}

void Note::setCollection(std::shared_ptr<Collection> col) {
    collection = col;
}

std::shared_ptr<Collection> Note::getCollection() const {
    return collection.lock();
}




