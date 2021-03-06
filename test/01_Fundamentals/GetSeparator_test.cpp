
#include "ink.hpp"

#include "catch.hpp"

#include <iostream>

TEST_CASE("Zero-initialization separator test", "[Ink::SEP]") {

    Ink::Separators c{};
    REQUIRE(c == Ink::Separators::Undefined);
}

TEST_CASE("Verify that separator is correct", "[Ink::SEP]") {

    Ink::Separators c = Ink::GetSeparator();

    // Verify that platform-specific separator is being
    // propagated correctly

    std::string prefix("src");
    std::string suffix("GUI");

    #ifdef _MSC_VER
    std::string sep("\\");
    #else
    std::string sep("/");
    #endif

    std::string out(1, static_cast<char>(c));

    REQUIRE(out == sep);

    // make sure it is easy to use with std::string
    REQUIRE(prefix + out + suffix == prefix + sep + suffix);
}
