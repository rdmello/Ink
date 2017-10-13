
## Ink - Build C++ using C++

A build system for C++ projects which uses C++ as the main configuration language. 

### Usage

Download the 'ink.cpp' file and add your dependencies using the Ink API.

Use the appropriate build command for your operating system to compile the 'ink.cpp' file:

    g++ ink.cpp -o ink.run
    
    clang++ ink.cpp -o ink.run

    cl.exe /EHsc ink.cpp  -o ink.run

The above command builds a binary file called 'ink.run'. Execute the 'ink.run' file on your command line to build your project. 

### Features

* Cross-platform compatibility

* C++14 minimum support with modern constructs

* only rebuild what you've changed

* parallel builds

* Easy setup - just one C++ file needs to be added to your project. no libraries or installers necessary. no admin permissions necessary

### Compatibility

This project is geared primarily at Linux, macOS, and Windows operating systems. The focus is on the following compilers on each platform: 

* Linux: GCC and Clang

* macOS: Clang and GCC

* Windows: Visual Studio 2012, 2015, 2017 and MinGW-w64 (TODO: should there be a Cygwin compiler here too?)

I would like to eventually add support for mobile compilers and additional platforms (like microcontrollers maybe) too. 



