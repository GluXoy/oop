#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../crypt/processByteStream.h"
#include "../crypt/stdafx.h"

TEST_CASE("Encode function correctly encodes bytes") {
    REQUIRE(Encode(0x12) == (unsigned char)0x39);
    REQUIRE(Encode(0x34) == (unsigned char)0x1A);
    // Другие проверки по аналогии
}

// Тест для функции Decode
TEST_CASE("Decode function correctly decodes bytes") {
    REQUIRE(Decode(0x39) == (unsigned char)0x12);
    REQUIRE(Decode(0x1A) == (unsigned char)0x34);
    // Другие проверки по аналогии
}
