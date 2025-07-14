cmake_minimum_required(VERSION 3.26)
project(Notes_1)

# Imposta il C++17 per tutto il progetto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Codice del progetto
add_executable(Notes_1
        main.cpp
        Note.cpp Note.h
        Collection.cpp Collection.h
        Observer.cpp Observer.h
        NoteManager.cpp NoteManager.h
        CollectionObserver.cpp CollectionObserver.h
        NoteApp.cpp NoteApp.h
)

# GoogleTest
add_subdirectory(googletest)

# Eseguibile per i test
add_executable(Tests
        tests/test_main.cpp
        tests/test_note.cpp
        tests/test_collection.cpp
        tests/test_manager.cpp

        # -- CORREZIONE: Aggiungi i file sorgente da testare --
        Note.cpp
        Collection.cpp
        NoteManager.cpp
        Observer.cpp
        CollectionObserver.cpp
        # Nota: Non serve aggiungere NoteApp.cpp perché non lo stai testando qui
)

# Collega le librerie di Google Test
target_link_libraries(Tests
        gtest
        gtest_main
)

# Assicura che i test possano trovare i file header del progetto
target_include_directories(Tests PRIVATE
        ${PROJECT_SOURCE_DIR}
)
