cmake_minimum_required(VERSION 3.0.0)
project(lab.programmazione VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
include(CTest)
enable_testing()

add_executable(lab.programmazione 
    src/main.cpp
    src/Subject.h
    src/Observer.h
    src/Note.h
    src/Editor.h
    src/Collection.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
