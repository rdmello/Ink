
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
    /*
     * Ink::Str is a cross-platform abstraction for strings
     */
    struct Str
    {
        std::string win32, win64, macOS, lnx32, lnx64;
        Str(const std::string&);            // sets all platform strings
        void setWin(const std::string&);    // sets win64 and win32
        void setUnix(const std::string&);   // sets macOS, lnx32, and lnx64
        void setLnx(const std::string&);    // sets lnx32 and lnx64
    };

    /* Cross-platform separator, changes to backslash on Windows */
    std::string SEP = "/"; 

    /* 
     * Identifying Target files 
     */
    enum class IDType {Str, FileName, FileNameMatcher, Label};

    struct Node
    {
        IDType type;
        std::string str;
    };

    Node File(std::string filename);
    Node FileNameMatcher(std::string matchstring);
    Node Label(std::string label);

    struct Target
    {
        Node output; 
        std::vector<Node> input;
        Str command;
    };

    int MakeBuilder(int argc, char** argv, Target t);
}

int main (int argc, char** argv)
{
    Ink::Target maindep{{Ink::IDType::FileName, ""}, {{Ink::IDType::FileName, ""}}, std::string("")};
    maindep.input.push_back(Ink::Node{Ink::IDType::FileName, "test" + Ink::SEP + "hello.cpp"});
    maindep.output = Ink::Node{Ink::IDType::FileName, "target" + Ink::SEP + "hello.run"};
    maindep.command.setUnix("clang++ -Wall -Werror -std=c++14 " + maindep.input[1].str + " -o " + maindep.output.str);
    maindep.command.setWin("cl.exe /EHsc test" + Ink::SEP + "hello.cpp");

    return Ink::MakeBuilder(argc, argv, maindep);
}

/*
 * Set the compiler-specific filename separator
 */
#ifdef _MSC_VER
    Ink::SEP = "\\";
#endif

Ink::Str::Str(const std::string& s): win32{s}, win64{s}, macOS{s},
lnx32{s}, lnx64{s} {};

void Ink::Str::setWin(const std::string& s)
{
    this->win32 = s;
    this->win64 = s;
}

void Ink::Str::setUnix(const std::string& s)
{
    this->macOS = s;
    this->lnx32 = s;
    this->lnx64 = s;
}

void Ink::Str::setLnx(const std::string& s)
{
    this->lnx32 = s;
    this->lnx64 = s;
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
        std::cout << t.command.macOS << std::endl;
        std::system(t.command.macOS.c_str());
    }
    
    return 0;
}

