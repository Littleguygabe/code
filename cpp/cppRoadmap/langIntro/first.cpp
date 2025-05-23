#include <iostream>
// intro to language 
// roadmap link -> https://roadmap.sh/cpp
int main(){
    int numinp; // need to declare like c
    
    std::cout<<"give me a number: ";
    std::cin>>numinp;
    std::cout<<"the number you gave me is: "<<numinp<<std::endl;
    
    // has the same control structure as c
    if (numinp>9){
        std::cout<<"double digits!!"<<std::endl;
    }
    else{
        std::cout<<"single digit!!"<<std::endl;
    }
    
    
    return 0;
}
