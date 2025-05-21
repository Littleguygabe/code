#include <stdio.h>
#include <pthread.h>

void *printHello(void * arg){
    while(1){
        printf("hello world\n");
    }
}

void *printBye(void * arg){
    while (1)
    {
        printf("Good bye\n");
    }
    
}

int main(int argc, char **argv){
    pthread_t one,two;

    pthread_create(&one,NULL,&printHello,NULL);/*creates the threads to run from*/
    pthread_create(&two,NULL,&printBye,NULL);

    pthread_join(one,NULL);/*ensure that the program doesnt end until threads have */
    pthread_join(two,NULL);/*finished running*/

    return 0;
}