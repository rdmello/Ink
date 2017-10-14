
#include "ink.hpp"

#include "catch.hpp"

TEST_CASE("Check zero-initialized values ARCH", "[Ink::ARCHITECTURE]") {

    // zero-initialize the object (do not default-initialize)
    Ink::Architectures c{};
    
    // We want to ensure that Ink::Context fields indicate
    // failure states when they occur. 
    // Therefore, all fields are set to "Unknown" by default

    REQUIRE(c == Ink::Architectures::Undefined);
}


TEST_CASE("Verify that correct architecture is detected", "[Ink::ARCHITECTURE]") {

    auto c = Ink::GetArchitectures();
    REQUIRE(c == Ink::Architectures::AMD64);
}

