
#include <iostream>

#include "../src/ink_pre.hpp"

#include "catch.hpp"

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

    REQUIRE(&c.Separator == sep);

    // make sure it is easy to use with std::string
    REQUIRE(prefix + &c.Separator + suffix == prefix + sep + suffix);
}

#include "../src/ink_post.hpp"
