#include "firstPackage.h"

int main(){

    packagePrint();

    return 0;
}

// when compiling need to make sure that i compile both files in the compile command to create
// a single executeable that can access all the code it needs.

// clang++ main.cpp firstPackage.cpp -o main

// compiles to executeable called 'main'