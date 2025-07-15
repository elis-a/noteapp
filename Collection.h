//
// Created by elisa on 18/06/2025.
//

#ifndef NOTES_1_COLLECTION_H
#define NOTES_1_COLLECTION_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Note.h"
#include "Observer.h"

class Collection : public std::enable_shared_from_this<Collection> {        // Per poter ottenere in modo sicuro uno shared pointer a sè stesso
public:
    explicit Collection(const std::string& name);

    const std::string& getName() const;

    void addNote(const std::shared_ptr<Note>& note);
    bool removeNote(const std::string& title);

    const std::vector<std::shared_ptr<Note>>& getNotes() const;
    std::shared_ptr<Note> getNote(const std::string& title) const;

    void attachObserver(Observer* observer);
    void detachObserver(Observer* observer);

private:
    std::string name;
    std::vector<std::shared_ptr<Note>> notes;
    std::vector<Observer*> observers;

    void notifyObservers() const;
};


#endif //NOTES_1_COLLECTION_H
