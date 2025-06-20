//
// Created by elisa on 20/06/2025.
//

#ifndef NOTES_1_COLLECTIONOBSERVER_H
#define NOTES_1_COLLECTIONOBSERVER_H

#include "Observer.h"
#include <iostream>

class CollectionObserver : public Observer {
public:
    void onCollectionChanged(const Collection& collection, std::size_t newSize) override;

};


#endif //NOTES_1_COLLECTIONOBSERVER_H
