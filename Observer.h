//
// Created by elisa on 18/06/2025.
//

#ifndef NOTES_1_OBSERVER_H
#define NOTES_1_OBSERVER_H

#include <cstddef>
#include <string>

class Collection;

class Observer {
public:
    virtual ~Observer() = default;

    virtual void onCollectionChanged(const Collection& collection, std::size_t newSize) = 0;

};


#endif //NOTES_1_OBSERVER_H
