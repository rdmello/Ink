
#include <iostream>

#include "../src/ink_pre.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test hello", "[Ink::SEP]") {

    Ink::Context c = Ink::GetContext();

    #ifdef _MSC_VER
    REQUIRE(c.Separator == std::string("\\"));
    #else
    REQUIRE(&c.Separator == std::string("/"));
    #endif
}

#include "../src/ink_post.hpp"
