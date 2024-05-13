cmake_minimum_required(VERSION 3.27)
project(yadro_test)

set(CMAKE_CXX_STANDARD 17)

add_executable(yadro_test main.cpp tape.cpp tape.h tape-abstract.h
        utils.h
        utils.cpp
        Delays.cpp
        Delays.h
        Sorting.cpp
        Sorting.h
        CountsCollection.h
        VectorCountsCollection.cpp
        VectorCountsCollection.h
        TapeCountsCollection.cpp
        TapeCountsCollection.h)
