#include <iostream>

int calculator(char op, int a,int b){
    switch(op){
        case '+':
        return a+b;
        case '-':
        return a-b;
        case '/':
        return a/b;
        case '*':
        return a*b;
    
    default:
        std::cout<<"invalid op"<<std::endl;
        return -1;
    }
}

int main(){
    int a,b;
    char op;

    while(true){
        std::cout<<"enter the first num: ";
        std::cin>>a;
        std::cout<<"enter the second num: ";
        std::cin>>b;
        std::cout<<"enter the op: ";
        std::cin>>op;
        std::cout<<"result: "<<calculator(op,a,b)<<std::endl;
    }
}