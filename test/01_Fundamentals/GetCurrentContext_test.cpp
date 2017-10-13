
#include "ink_pre.hpp"

#include "catch.hpp"

TEST_CASE("Check default values", "[Ink::Platform]") {

    // zero-initialize the object (do not default-initialize)
    Ink::Context c{};
    
    // We want to ensure that Ink::Context fields indicate
    // failure states when they occur. 
    // Therefore, all fields are set to "Unknown" by default

    REQUIRE(c.Platform == Ink::Platforms::Unknown);
    REQUIRE(c.Compiler == Ink::Compilers::Unknown);
    REQUIRE(c.Bitness  == Ink::Bitnesses::Unknown);
    REQUIRE(c.Separator  == Ink::Separators::Unknown);
}


TEST_CASE("Verify that correct platform is detected", "[Ink::Platform]") {

    Ink::Context c = Ink::GetCurrentContext();

    

}

