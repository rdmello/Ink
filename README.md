
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





