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

set_target_properties(Serialization PROPERTIES
        FRAMEWORK TRUE
        VERSION "1.0.0"
        SOVERSION "1.0.0"
        FRAMEWORK_VERSION "A"
        PUBLIC_HEADER Serialization/Source/Public/Serializable.h)

# XCTest for Framework

enable_testing()

find_package(XCTest REQUIRED)

xctest_add_bundle(SerializationTests Serialization)

target_sources(SerializationTests
        PRIVATE
        SerializationTests/Source/Private/Assert.cpp
        SerializationTests/Source/Private/Assert.mm
        SerializationTests/Source/Private/SerializationTests.cpp
        SerializationTests/Source/Private/SerializationTests.mm
        SerializationTests/Source/Private/TestsImplementations.cpp)

include_directories(SerializationTests/Source/Public/)
