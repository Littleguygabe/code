#include <cstddef>
#include <iostream>
#include <string>
#include <vector>


class Menu{
    public:
        void printMenu(){
            std::cout<<"Select an option from below:"<<std::endl;
            std::cout<<"[C]reate new task"<<std::endl;
            std::cout<<"[V]iew current tasks"<<std::endl;
            std::cout<<"[E]xit the program"<<std::endl;
            return;
        }

        char getUserInput(){
            char userInp;
            std::cout<<": ";
            std::cin>>userInp;
            std::cin.ignore();
            return userInp;
        }   
};

class Task{
    private:
        std::string name;
        std::string desc;


    public:
        Task (std::string name,std::string desc){
            this->name = name;
            this->desc = desc;
        }

        std::string getName(){
            return name;
        }

        std::string getDesc(){
            return desc;
        }

};

class TaskManager{
    private:
        Menu MenuController = Menu();
        bool Running = true;
        std::vector<class Task> tasks = {};

        void decodeInput(char userInp){
            switch(userInp){
                case 'E':
                    Running = false;
                    break;

                case 'C':
                    createNewTask();
                    break;

                case 'V':
                    listTasks();
                    break;

                default:
                    std::cout<<"Please Choose a Valid Option"<<std::endl<<std::endl;
                    break;
            }
        }

        void createNewTask(){
            std::string name,desc;



            std::cout<<"enter the name of the new task: ";
            std::getline(std::cin,name);

            std::cout<<"enter the decription of the new task: ";
            std::getline(std::cin,desc);

            Task newTask(name,desc);

            tasks.push_back(newTask);

            return;

        }

        void listTasks(){
            char detail;
            std::cout<<"Do you want the Detailed Output? (y/n) ";
            std::cin>>detail;
            std::cout<<std::endl<<"Current Tasks:"<<std::endl;
            if (tasks.size()==0){
                std::cout<<"No Current Tasks"<<std::endl;
            }
            else{
                for (size_t i = 0; i<tasks.size();i++){
                    std::cout<<i+1<<". "<<tasks[i].getName();

                    if(detail == 'y'){
                        std::cout<<" -> "<<tasks[i].getDesc()<<std::endl;
                    }
                    else{
                        std::cout<<std::endl;
                    }

                }
            }

            return;
        }

    public:
        TaskManager(){
            char userInp;
            while (Running){
                MenuController.printMenu();
                userInp = MenuController.getUserInput();
                decodeInput(userInp);
            }    
            

        }

};


int main(){
    TaskManager taskManager;

    return 0;
}