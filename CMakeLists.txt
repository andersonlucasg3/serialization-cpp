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

if (!WIN32)

set_target_properties(Serialization PROPERTIES
        FRAMEWORK TRUE
        VERSION "1.0.0"
        SOVERSION "1.0.0"
        FRAMEWORK_VERSION "A"
        PUBLIC_HEADER Serialization/Source/Public/Serializable.h)

endif(!WIN32)

enable_testing()

set(TEST_SOURCES_CPP
        SerializationTests/Source/Private/Assert.cpp
        SerializationTests/Source/Private/SerializationTests.cpp
        SerializationTests/Source/Private/TestsImplementations.cpp)

if (!WIN32)

    # XCTest for Framework

    find_package(XCTest REQUIRED)

    xctest_add_bundle(SerializationTests Serialization)

    target_sources(SerializationTests
            PRIVATE
            "${TEST_SOURCES}"
            SerializationTests/Source/Private/Assert.mm
            SerializationTests/Source/Private/SerializationTests.mm)

    include_directories(SerializationTests/Source/Public/)

else()

    add_executable(SerializationTests "${TEST_SOURCES_CPP}")
    target_link_libraries(SerializationTests Serialization)
    add_test(NAME SerializationTests COMMAND SerializationTests)

    include_directories(SerializationTests/Source/Public/)

endif(!WIN32)