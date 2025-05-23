#include "firstPackage.h" // include for good practice -> means compiler can catch errors 
// rather than the linker
#include <iostream>

void packagePrint(){
    std::cout<<"printing from the package"<<std::endl;
    std::cout<<"testing the chained shortcuts"<<std::endl;
    std::cout<<"does this work aswel??"<<std::endl;
    std::cout<<"no it does not :("<<std::endl;

}