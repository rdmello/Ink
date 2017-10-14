
#include "ink.hpp"

#include "catch.hpp"

TEST_CASE("Test Node Constructors", "[Ink::Node]")
{
    /* 
     * Check that default initialization is placing the
     * object in the correct state
     */
    Ink::Node n1;

    REQUIRE(n1.outputs.size() == 0);
    REQUIRE(n1.inputs.size() == 0);
    REQUIRE(n1.commands.size() == 0);

    /* 
     * Test constructor with const char* output file name     
     */
    Ink::Node n2("myfile.txt");

    REQUIRE(n2.outputs[0] == "myfile.txt");
    REQUIRE(n2.outputs.size() == 1);
    REQUIRE(n2.inputs.size() == 0);
    REQUIRE(n2.commands.size() == 0);
    
    /* 
     * Test constructor with std::string output file name     
     */
    std::string mystr("myfile.txt");
    Ink::Node n3(mystr);

    REQUIRE(n3.outputs[0] == "myfile.txt");
    REQUIRE(n3.outputs.size() == 1);
    REQUIRE(n3.inputs.size() == 0);
    REQUIRE(n3.commands.size() == 0);
}

TEST_CASE("Test Node Setters", "[Ink::Node]") 
{
    /*
     * Adding elements to the input, output, and command list
     */
    Ink::Node n0("initial_outfile.cpp");
    n0.inputs.push_back("an_file.cpp");
    REQUIRE(n0.outputs.at(0) == "initial_outfile.cpp");
    
    /*
     * Verify that the child node has been constructed correctly
     */
    REQUIRE(n0.inputs.at(0).inputs.size() == 0);
    REQUIRE(n0.inputs.at(0).outputs.size() == 1);
    REQUIRE(n0.inputs.at(0).commands.size() == 0);
    REQUIRE(n0.inputs.at(0).outputs.at(0) == "an_file.cpp");
    
    /*
     * Set build command
     */    
    n0.commands.push_back("build stuff");
    REQUIRE(n0.commands.at(0) == "build stuff");
}