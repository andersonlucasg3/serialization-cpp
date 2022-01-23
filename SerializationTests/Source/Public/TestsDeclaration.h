#pragma once

#include "FieldDataTests.h"
#include "SerializableTests.h"
#include "ByteArrayTests.h"

#define DECLARE_ALL_TEST_CLASSES() \
DECLARE_TEST_CLASS(FieldDataTests, DECLARE_FIELD_DATA_TESTS()) \
DECLARE_TEST_CLASS(SerializableTests, DECLARE_SERIALIZABLE_TESTS()) \
DECLARE_TEST_CLASS(ByteArrayTests, DECLARE_BYTE_ARRAY_TESTS())
