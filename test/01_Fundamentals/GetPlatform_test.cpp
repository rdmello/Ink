
#include "ink.hpp"

#include "catch.hpp"

#include <iostream>

TEST_CASE("Zero-initialization platform test", "[Ink::PLATFORM]") {

    Ink::Platforms c{};
    REQUIRE(c == Ink::Platforms::Undefined);
}

TEST_CASE("Verify that platform is correct", "[Ink::PLATFORM]") {

    Ink::Platforms c = Ink::GetPlatform();
    REQUIRE(c == Ink::Platforms::macOS);
}
