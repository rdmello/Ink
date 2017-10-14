
#include "ink.hpp"

#include "catch.hpp"

TEST_CASE("Check zero-initialized values COMPILER", "[Ink::COMPILER]") {

    // zero-initialize the object (do not default-initialize)
    Ink::Compilers c{};
    
    // We want to ensure that Ink::Context fields indicate
    // failure states when they occur. 
    // Therefore, all fields are set to "Undefined" by default

    REQUIRE(c == Ink::Compilers::Undefined);
}


TEST_CASE("Verify that correct compiler is detected", "[Ink::COMPILER]") {

    auto c = Ink::GetCompiler();
    REQUIRE(c== Ink::Compilers::Clang);
}

