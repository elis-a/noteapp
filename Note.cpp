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

// Imposta o aggiorna il testo della nota
void Note::setText(const std::string& newText) {
    text = newText;
}

// Inverte lo stato di blocco della nota, passando da bloccata a sbloccata o viceversa
void Note::toggleLock() {
    locked = !locked;
}

// Inverte lo stato di importanza della nota, passando da importante a non importante o viceversa
void Note::toggleImportant() {
    important = !important;
}




