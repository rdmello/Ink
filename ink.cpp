
/*
 * Ink - A simple C++ build system
 *
 * This file contains the entire Ink build system.
 *
 * Read the first part of the file to understand the common data structures
 * and use the Ink:: namespaced data types and functions to write a 
 * build script.
 *
 */

#include <iostream>
#include <string>
#include <vector>

/* for 'system()' */
#include <cstdlib>

namespace Ink
{
    struct Target
    {
        std::string filename;
        std::vector<std::string> deplist;
        std::string buildrule;
    };

    int MakeBuilder(Target);

    enum class InputType {
        All
    };
}

int main (int argc, char** argv)
{
    std::cout << "Hello" << std::endl;

    Ink::Target maindep{
        "out.run",
        {"test/hello.cpp"},
        "clang++ -Wall -Werror test/hello.cpp -o target/hello.run"
    }; 
    
    return Ink::MakeBuilder(maindep);
}

int Ink::MakeBuilder(Ink::Target t)
{
    std::system(t.buildrule.c_str());
    return 0;
}

