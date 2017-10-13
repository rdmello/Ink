
#include "ink_pre.hpp"

#include "catch.hpp"

#include <iostream>

TEST_CASE("Verify that separator is correct", "[Ink::SEP]") {

    Ink::Context c = Ink::GetCurrentContext();

    // Verify that platform-specific separator is being
    // propagated correctly

    std::string prefix("src");
    std::string suffix("GUI");

    #ifdef _MSC_VER
    std::string sep("\\");
    #else
    std::string sep("/");
    #endif

    std::string out(1, static_cast<char>(c.Separator));

    REQUIRE(out == sep);

    // make sure it is easy to use with std::string
    REQUIRE(prefix + out + suffix == prefix + sep + suffix);
}
