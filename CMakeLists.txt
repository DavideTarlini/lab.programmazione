cmake_minimum_required(VERSION 3.0.0)
project(lab.programmazione VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab.programmazione 
    src/main.cpp
    src/Subject.h
    src/Observer.h
    src/Note.h
    src/Collection.h
    src/CollectionObserver.h
)

enable_testing()
add_subdirectory(test) 
