
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

    int MakeBuilder(int argc, char** argv, Target t);
}

int main (int argc, char** argv)
{
    Ink::Target maindep {
        "target/hello.run",
        {"test/hello.cpp"},
        "clang++ -Wall -Werror test/hello.cpp -o target/hello.run"
    }; 
    
    return Ink::MakeBuilder(argc, argv, maindep);
}

int Ink::MakeBuilder(int argc, char** argv, Ink::Target t)
{
    // for (int i = 0; i < argc; ++i)
    // {
    //     std::cout << "Input " << i << ": " << argv[i] << std::endl;
    // }

    if (argc > 1) 
    {
        if (argv[1] == std::string("clean"))
        {
            std::string fullcmd = "rm -f " + t.filename;
            std::cout << fullcmd << std::endl;
            std::system(fullcmd.c_str());
        }
    } 
    else 
    {
        std::cout << t.buildrule << std::endl;
        std::system(t.buildrule.c_str());
    }
    
    return 0;
}

