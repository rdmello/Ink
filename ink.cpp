
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
    /* Identifying Target files */
    enum class IDType {FileName, FileNameMatcher, Label};

    struct Identifier
    {
        IDType type;
        std::string str;
    };

    Identifier File(std::string filename);
    Identifier FileNameMatcher(std::string matchstring);
    Identifier Label(std::string label);

    struct Target
    {
        Identifier output; 
        std::vector<Identifier> input;
        std::string command;
    };

    int MakeBuilder(int argc, char** argv, Target t);
}

int main (int argc, char** argv)
{
    // Ink::Target maindep {
    //     "target/hello.run",
    //     {"test/hello.cpp"},
    //     "clang++ -Wall -Werror test/hello.cpp -o target/hello.run"
    // };

    Ink::Target maindep {
        {Ink::IDType::FileName, "target\\hello.run"},
        {{Ink::IDType::FileName, "test\\hello.cpp"}},
    };
    maindep.command = "cl.exe /EHsc test\\hello.cpp";
    
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
            std::string fullcmd = "rm -f " + t.output.str;
            std::cout << fullcmd << std::endl;
            std::system(fullcmd.c_str());
        }
    } 
    else 
    {
        std::cout << t.command << std::endl;
        std::system(t.command.c_str());
    }
    
    return 0;
}

