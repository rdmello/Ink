
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
