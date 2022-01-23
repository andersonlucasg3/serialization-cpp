cmake_minimum_required(VERSION 3.21.1)

project(serialization-cpp)

set(CMAKE_CXX_STANDARD 17)

add_library(Serialization
        Serialization/Source/Private/ByteArray.cpp
        Serialization/Source/Private/FieldData.cpp
        Serialization/Source/Private/Serializable.cpp
        Serialization/Source/Private/SerializableField.cpp
        Serialization/Source/Private/ByteArray.h
        Serialization/Source/Public/FieldData.h
        Serialization/Source/Public/Serializable.h
        Serialization/Source/Public/SerializableField.h
        Serialization/Source/Public/TemplateInstantiation.hpp)

target_include_directories(Serialization
        PUBLIC
        Serialization/Source/Public/)

if (APPLE)

set_target_properties(Serialization PROPERTIES
        FRAMEWORK TRUE
        VERSION "1.0.0"
        SOVERSION "1.0.0"
        FRAMEWORK_VERSION "A"
        PUBLIC_HEADER Serialization/Source/Public/Serializable.h)

endif(APPLE)

enable_testing()

set(TEST_SOURCES_CPP
        SerializationTests/Source/Private/FieldDataTests.cpp
        SerializationTests/Source/Private/SerializableTests.cpp
        SerializationTests/Source/Private/ByteArrayTests.cpp
        SerializationTests/Source/Public/Assert.h
        SerializationTests/Source/Public/FieldDataTests.h
        SerializationTests/Source/Public/SerializableTests.h
        SerializationTests/Source/Public/ByteArrayTests.h
        SerializationTests/Source/Public/TestsDeclaration.h)

if (APPLE)

    # XCTest for Framework

    find_package(XCTest REQUIRED)

    xctest_add_bundle(SerializationTests Serialization)

    list(APPEND TEST_SOURCES_CPP 
        SerializationTests/Source/Private/Assert.mm
        SerializationTests/Source/Private/SerializationTests.mm)

    target_sources(SerializationTests PRIVATE "${TEST_SOURCES_CPP}")

    include_directories(SerializationTests/Source/Public/)

else()

    list(APPEND TEST_SOURCES_CPP
        SerializationTests/Source/Private/Assert.cpp
        SerializationTests/Source/Private/SerializationTests.cpp)

    add_library(SerializationTests SHARED "${TEST_SOURCES_CPP}")
    set_target_properties(SerializationTests PROPERTIES
            DLL TRUE)
    add_test(SerializationTests COMMAND SerializationTests)
    target_link_libraries(SerializationTests Serialization)

    include_directories(SerializationTests/Source/Public/)

endif(APPLE)
