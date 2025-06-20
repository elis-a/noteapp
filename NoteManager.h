//
// Created by elisa on 18/06/2025.
//

#ifndef NOTES_1_NOTEMANAGER_H
#define NOTES_1_NOTEMANAGER_H
#include <memory>
#include <unordered_map>
#include <vector>
#include "Collection.h"


class NoteManager {
public:
    void createCollection(const std::string& name);
    void deleteCollection(const std::string& name);
    std::shared_ptr<Collection> getCollection(const std::string& name) const;
    bool hasCollection(const std::string& name) const;

    std::vector<std::string> listCollectionNames() const;

    std::shared_ptr<Note> findNoteInAllCollection(const std::string& title) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Collection>> collections;
};


#endif //NOTES_1_NOTEMANAGER_H
