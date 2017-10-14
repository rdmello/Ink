
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
     * INK PLATFORM, PATH, AND FILENAME UTILITIES   * 
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
     * INK BUILD NODES AND DEPENDENCY HIERARCY FCNS * 
     ************************************************/

    struct Node
    {
        std::string output; 
        std::vector<Node> inputs;
        std::string command;
    };
    
    Node File(std::string filename);
    std::vector<Node> FileNameMatcher(std::string matchstring);
    Node Label(std::string label);

    int MakeBuilder(int argc, char** argv, Node t);

    #define INK_PRE_DEFINE
}

#endif /* INK_PRE_HEADER */
