
#include <iostream>

/* for 'system()' */
#include <cstdlib>

#include "ink.hpp"

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
        return Architectures::Unknown;
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

Node::Node(const std::string &outputFilename) : outputs(), inputs(), commands() { outputs.push_back(outputFilename); }

Node::Node(const char *outputFilename) : outputs(), inputs(), commands() { outputs.push_back(std::string(outputFilename)); }

int MakeBuilder(int argc, char **argv, Ink::Node t)
{
        return 0;
}
}
