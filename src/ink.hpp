
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

    /* 
     * Merge individual filenames into a space-separated,
     * comma-separated list (without extra trailing separator)
     * The last argument is the separator in both cases
     */
    std::string merge(std::vector<std::string>, std::string);

    /*
     * Ink::Str is a cross-platform abstraction for strings
     */
    struct Str
    {
        std::string win32, win64, macOS, lnx32, lnx64;
        Str(const std::string&);            // sets all platform strings
        void setWindows(const std::string&);    // sets if win64 or win32
        void setUnix(const std::string&);   // sets if macOS, lnx32, or lnx64
        void setLinux(const std::string&);    // sets if lnx32 or lnx64
    };

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

    #define INK_PRE_DEFINE
}

#endif /* INK_PRE_HEADER */
