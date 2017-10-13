
#include "ink.hpp"

#include "catch.hpp"

TEST_CASE("Check zero-initialized values", "[Ink::Platform]") {

    // zero-initialize the object (do not default-initialize)
    Ink::Context c{};
    
    // We want to ensure that Ink::Context fields indicate
    // failure states when they occur. 
    // Therefore, all fields are set to "Unknown" by default

    REQUIRE(c.Platform == Ink::Platforms::Unknown);
    REQUIRE(c.Compiler == Ink::Compilers::Unknown);
    REQUIRE(c.Architecture == Ink::Architectures::Unknown);
    REQUIRE(c.Separator == Ink::Separators::Unknown);
}


TEST_CASE("Verify that correct platform is detected", "[Ink::Platform]") {

    Ink::Context c = Ink::GetCurrentContext();

    REQUIRE(c.Platform == Ink::Platforms::macOS);
    REQUIRE(c.Compiler == Ink::Compilers::Clang);
    REQUIRE(c.Architecture == Ink::Architectures::AMD64);
    REQUIRE(static_cast<char>(c.Separator) == '/');
}

