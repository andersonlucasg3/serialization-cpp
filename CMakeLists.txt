cmake_minimum_required(VERSION 3.21.1)

project(serialization-cpp)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME GroupSourcesByFolder.cmake
  GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
  VERSION 1.0
)

add_subdirectory(GroupSourcesByFolder)

set(CMAKE_CXX_STANDARD 17)

add_library(Serialization
            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Private/Serializable.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Private/FieldData.cpp"

            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Public/MemoryBuffer.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Public/Serializable.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Public/FieldData.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Serialization/Source/Public/SerializableField.h")

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
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/FieldDataTests.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/SerializableTests.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/MemoryBufferTests.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Public/Test.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Public/FieldDataTests.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Public/SerializableTests.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Public/MemoryBufferTests.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Public/TestsDeclaration.h")

if (APPLE)

    # XCTest for Framework

    find_package(XCTest REQUIRED)

    xctest_add_bundle(SerializationTests Serialization)

    list(APPEND TEST_SOURCES_CPP
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/SerializationTests.mm"
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/Test.mm")

    target_sources(SerializationTests PRIVATE "${TEST_SOURCES_CPP}")

    include_directories(SerializationTests/Source/Public/)

else()

    list(APPEND TEST_SOURCES_CPP
            "${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests/Source/Private/SerializationTests.cpp")

    add_library(SerializationTests SHARED "${TEST_SOURCES_CPP}")
    set_target_properties(SerializationTests PROPERTIES DLL TRUE)
    add_test(SerializationTests COMMAND SerializationTests)
    target_link_libraries(SerializationTests Serialization)

    include_directories(SerializationTests/Source/Public/)

endif(APPLE)

GroupSourcesByFolder(Serialization)
GroupSourcesByFolder(SerializationTests)
