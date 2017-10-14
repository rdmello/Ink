
#include <iostream>

/* for 'system()' */
#include <cstdlib>

#include "ink.hpp"

namespace Ink
{
Context GetCurrentContext()
{
    return Ink::Context{
// check Platforms
#ifdef _WIN32
        Platforms::Windows,
#elif __APPLE__ && __MACH__
        Platforms::macOS,
#elif __linux__
        Platforms::linux,
#else
        Platforms::Undefined,
#endif
// Check compilers
#ifdef _MSC_VER
        Compilers::VS,
#elif __clang__
        Compilers::Clang,
#elif __GNUC__
        Compilers::GCC,
#else
        Compilers::Undefined,
#endif
// Check architecture
#if _MSC_VER && _M_IX86
        Architectures::x86,
#elif __GNUC__ && __i386__ && (!__amd64__)
        Architectures::x86,
#elif (_MSC_VER && _M_X64) || (__GNUC__ && __amd64__)
        Architectures::AMD64,
#else
        Architectures::Unknown,
#endif
// set separator
#ifdef _MSC_VER
        Separators::BackSlash
#else
        Separators::Slash
#endif
    };
}

int MakeBuilder(int argc, char **argv, Ink::Node t)
{
    if (argc > 1)
    {
        if (argv[1] == std::string("clean"))
        {
            std::string fullcmd = "rm -f " + t.output;
            std::cout << fullcmd << std::endl;
            std::system(fullcmd.c_str());
        }
    }

    return 0;
}
}
