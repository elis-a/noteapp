cmake_minimum_required(VERSION 3.26)
project(Notes_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Notes_1 main.cpp Note.cpp Note.h Collection.cpp Collection.h Observer.cpp Observer.h NoteManager.cpp NoteManager.h
        CollectionObserver.cpp
        CollectionObserver.h
        NoteApp.cpp
        NoteApp.h)
