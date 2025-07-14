//
// Created by elisa on 20/06/2025.
//

#include "CollectionObserver.h"
#include "Collection.h"

// Funzione che viene chiamata automaticamente ogni volta che una nota viene aggiunta/rimossa da una collezione. Stampa un messaggio che informa del cambiamento
void CollectionObserver::onCollectionChanged(const Collection& collection, std::size_t newSize) {
    std::cout <<"[Observer] Collection \""<< collection.getName()
        << "\" now has "<< newSize <<" notes(s)." << std::endl;
}
