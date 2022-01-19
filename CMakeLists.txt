cmake_minimum_required(VERSION 3.21)
project(Serialization)

set(CMAKE_CXX_STANDARD 17)

include_directories(Serialization)
include_directories(SerializationTests/Implementations)
include_directories(SerializationTests/TestFramework)

add_library(Serialization
        Serialization/Serializable.h
        Serialization/Serializable.cpp
        Serialization/FieldData.h
        Serialization/FieldData.cpp
        Serialization/TemplateInstantiation.hpp
        Serialization/SerializableField.cpp
        Serialization/SerializableField.h)

add_test(SerializationTests
        Serialization/TemplateInstantiation.hpp
        SerializationTests/Implementations/TestsImplementations.cpp
        SerializationTests/Implementations/TestsImplementations.h
        SerializationTests/macOS/SerializationTests.mm
        SerializationTests/TestFramework/macOS/Assert.mm
        SerializationTests/TestFramework/Assert.h)
