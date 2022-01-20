cmake_minimum_required(VERSION 3.21.1)
project(serialization-cpp)

set(CMAKE_CXX_STANDARD 17)

add_library(Serialization
        Serialization/Source/Private/FieldData.cpp
        Serialization/Source/Private/Serializable.cpp
        Serialization/Source/Private/SerializableField.cpp)

target_include_directories(Serialization
        PUBLIC
        Serialization/Source/Public/)

enable_testing()
add_test(SerializationTests
        SerializationTests/Source/Private/Assert.cpp
        SerializationTests/Source/Private/Assert.mm
        SerializationTests/Source/Private/SerializationTests.cpp
        SerializationTests/Source/Private/SerializationTests.mm
        SerializationTests/Source/Private/TestsImplementations.cpp)

include_directories(SerializationTests/Source/Public/)
