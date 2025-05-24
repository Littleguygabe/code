#include <iostream>

int main(){

    int input;
    std::cout<<"enter a number: ";
    std::cin>>input;

    while (input>9){
        std::cout<<"2 whole digits!! -> "<<input<<std::endl;
        std::cout<<"enter a number: ";
        std::cin>>input;
    }
    std::cout<<"1 whole digit!! -> "<<input<<std::endl;
    return 0;
}