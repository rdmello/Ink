
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

    enum class Platforms { Unknown, Windows, macOS, Linux };
    enum class Compilers { Unknown, VS, Clang, GCC };
    enum class Architectures { Unknown, x86, AMD64 };
    enum class Separators : char { Unknown, Slash = '/', BackSlash = '\\' };

    struct Context
    {
        Platforms Platform;
        Compilers Compiler;
        Architectures Architecture;
        Separators Separator;
    };

    Context GetCurrentContext();

    /************************************************
     * BUILD NODES AND DEPENDENCY HIERARCY FCNS     * 
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
     */

    struct Node
    {
        std::vector<std::string> outputs; 
        std::vector<Node> inputs;
        std::vector<std::string> commands;
        Node();
        Node(const std::string& outfilename);
        Node(const char* outfilename);
    };
    
    std::vector<Node> FileNameMatcher(std::string matchstring);
    Node Label(std::string label);

    int MakeBuilder(int argc, char** argv, Node t);
}

#endif /* INK_PRE_HEADER */
