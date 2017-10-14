
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
            if (res == Result::Failure)
                    return Result::Failure;
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
