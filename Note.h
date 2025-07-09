//
// Created by elisa on 18/06/2025.
//

#ifndef NOTES_1_NOTE_H
#define NOTES_1_NOTE_H

#include <string>
#include <memory>

class Collection;

class Note {
public:
    Note(const std::string& title, const std::string& text);

    const std::string& getTitle() const;
    const std::string& getText() const;
    bool isImportant() const;
    bool isLocked() const;

    void setText(const std::string& newText);
    void toggleLock();
    void toggleImportant();

private:
    std::string title;
    std::string text;
    bool important;
    bool locked;
};


#endif //NOTES_1_NOTE_H
