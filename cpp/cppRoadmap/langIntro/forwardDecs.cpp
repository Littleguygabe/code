#include <iostream>

// like in C if declare a function after its call then it will give error
// so need to pre-define like in c

// forward declaration
int add(int a,int b); // also called a function prototype


int main(){

    std::cout<<add(1,5)<<std::endl;    

    return 0;
}

int add(int a,int b){
    // return a+b;
    int c{a+b};
    return c; // return a+b;

    // the {} ensures that c is type safe, so if the result of the expression doesnt match the
    // type of c rather than casting it the program throws an error
    // which is why it is type safe so better practice to do this rather than defining the expr

}

