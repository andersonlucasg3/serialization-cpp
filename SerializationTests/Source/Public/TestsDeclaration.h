#pragma once

#include "FieldDataTests.h"
#include "SerializableTests.h"
#include "MemoryBufferTests.h"

#define DECLARE_ALL_TEST_CLASSES() \
DECLARE_TEST_CLASS(FieldDataTests, DECLARE_FIELD_DATA_TESTS()) \
DECLARE_TEST_CLASS(SerializableTests, DECLARE_SERIALIZABLE_TESTS()) \
DECLARE_TEST_CLASS(MemoryBufferTests, DECLARE_MEMORY_BUFFER_TESTS())
