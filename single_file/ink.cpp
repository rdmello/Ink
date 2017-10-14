
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

#include <string>
#include <vector>

#ifndef INK_PRE_HEADER
#define INK_PRE_HEADER

namespace Ink
{
    /************************************************
     * PLATFORM, PATH, AND FILENAME UTILITIES       * 
     ************************************************/

    enum class Platforms { Undefined, Windows, macOS, Linux };
    enum class Compilers { Undefined, VS, Clang, GCC };
    enum class Architectures { Undefined, x86, AMD64 };
    enum class Separators : char { Undefined, Slash = '/', BackSlash = '\\' };

    Platforms GetPlatform();
    Compilers GetCompiler();
    Architectures GetArchitectures();
    Separators GetSeparator();

    /************************************************
     * BUILD NODES AND DEPENDENCY HIERARCHY FCNS     * 
     ************************************************/

    /*
     * Ink::Node represents a build step for a single file:
     * - out:  output file name, 
     *            if provided, the existence of this file will
     *            be checked post-build
     *            to verify that the build process has completed
     *            successfully. 
     *            If the output file is not generated, Ink will
     *            error out
     * - in:  dependencies for this build step
     * - commands: actual build command executed using the std::system
     *             function
     * 
     * example: Ink::Node mybuild("helloworld.run");
     *          mybuild.inputs.push_back(Ink::Node("helloworld.cpp"));
     *          mybuild.command = "gcc " + mybuild.inputs[0] + " -o " + mybuild.output;
     *          Ink::Build(mybuild);
     */

    struct Node
    {
        std::vector<std::string> outputs; 
        std::vector<Node>        inputs;
        std::vector<std::string> commands;
        Node();
        Node(const std::string& outfilename);
        Node(const char* outfilename);
        // std::string printInputs(std::string delimiter = " ");
        // std::string printOutputs(std::string delimiter = " ");
        // std::string printCommands(std::string delimiter = " ");
    };
    
    std::vector<Node> FileNameMatcher(const std::string& matchstring);

    /************************************************
     * BUILD GENERATORS                             * 
     ************************************************/
    enum class Result { Failure, Success };
    Result Build(const Node&);
}

#endif /* INK_PRE_HEADER */

int main (int argc, char** argv)
{
    Ink::Node hello("hello.run");
    hello.inputs.push_back("hello.cpp");

    if (Ink::GetPlatform() == Ink::Platforms::Windows) {
        hello.commands.push_back( "cl.exe /EHsc " + hello.inputs[0].outputs[0] );
    } else {
        hello.commands.push_back( "g++ -Wall -Werror -std=c++11 "
            + hello.inputs[0].outputs[0]
            + " -o " + hello.outputs[0]
        );
    }

    Ink::Build(hello);
    return 0;
}

#include <iostream>

/* for 'system()' */
#include <cstdlib>

namespace Ink
{
    Platforms GetPlatform()
    {
        #ifdef _WIN32
            return Platforms::Windows;
        #elif __APPLE__ && __MACH__
            return Platforms::macOS;
        #elif __linux__
            return Platforms::Linux;
        #else
            return Platforms::Undefined;
        #endif
    }
    
    Compilers GetCompiler()
    {
        #ifdef _MSC_VER
            return Compilers::VS;
        #elif __clang__
            return Compilers::Clang;
        #elif __GNUC__
            return Compilers::GCC;
        #else
            return Compilers::Undefined;
        #endif
    }

    Architectures GetArchitectures()
    {
        #if _MSC_VER && _M_IX86
            return Architectures::x86;
        #elif __GNUC__ && __i386__ && (!__amd64__)
            return Architectures::x86;
        #elif (_MSC_VER && _M_X64) || (__GNUC__ && __amd64__)
            return Architectures::AMD64;
        #else
            return Architectures::Undefined;
        #endif
    }

    Separators GetSeparator()
    {
        #ifdef _MSC_VER
            return Separators::BackSlash;
        #else
            return Separators::Slash;
        #endif
    }

    Node::Node() : outputs(), inputs(), commands(){};

    Node::Node(const std::string &outputFilename) :
    outputs(), inputs(), commands() { outputs.push_back(outputFilename); }

    Node::Node(const char *outputFilename) :
    outputs(),
    inputs(),
    commands() { outputs.push_back(std::string(outputFilename)); }

    Result Build(const Ink::Node &root)
    {
        /* 
         * Iterate through child nodes and build them
         */
        for (const Node &child : root.inputs)
        {
            Result res = Build(child);
            if (res == Result::Failure) return Result::Failure;
        }

        /*
         * Execute build commands for this node
         */
        if (root.commands.size() > 0)
        {
            for (const std::string &cmd : root.commands)
            {
                    std::system(cmd.c_str());
            }
        }

        // TODO: check for existence of prebuilt file

        return Result::Success;
    }
}
