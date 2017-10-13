
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

/*
    * Set the compiler-specific filename separator
    */
Str::Str(const std::string &s) : win32(s), win64(s), macOS(s),
                                 lnx32(s), lnx64(s){};

void Str::setWindows(const std::string &s)
{
    this->win32 = s;
    this->win64 = s;
}

void Str::setUnix(const std::string &s)
{
    this->macOS = s;
    this->lnx32 = s;
    this->lnx64 = s;
}

void Str::setLinux(const std::string &s)
{
    this->lnx32 = s;
    this->lnx64 = s;
}

int MakeBuilder(int argc, char **argv, Ink::Target t)
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
}
