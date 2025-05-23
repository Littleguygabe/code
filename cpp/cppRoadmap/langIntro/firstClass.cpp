#include <iostream>
#include <string>

class MyClass{
    private:
        std::string firstName;
        std::string lastName;

    public:
        MyClass(std::string firstName, std::string lastName){
            firstName = firstName;
            lastName = lastName;
        }

        std::string getName(){
            return firstName+lastName;
        }

};

int main(){

    MyClass firstClass("Gabriel","Bridger");    

    std::string name = firstClass.getName();
    std::cout<<name;


    return 0;
}