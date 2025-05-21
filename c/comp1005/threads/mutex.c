#include <stdio.h>
#include <pthread.h>

unsigned long int total = 0;
pthread_mutex_t totalLock;

void *sum1(void * arg){
    unsigned long i;
    unsigned long localtotal=0;
    for (i=0;i<=50000000;i++){
       localtotal+=i;
   }
    
    pthread_mutex_lock(&totalLock);
    total+=localtotal;
    pthread_mutex_unlock(&totalLock);

}

void *sum2(void * arg){
    unsigned long i;
    unsigned long localtotal = 0;
    for (i=50000001;i<=100000000;i++){
       localtotal+=i; 
    }

    pthread_mutex_lock(&totalLock);
    total+=localtotal;
    pthread_mutex_unlock(&totalLock);
}

int main(int argc, char **argv){
    pthread_t one,two;
    pthread_mutex_init(&totalLock,NULL); /*mutex --> mutually exclusive, so waits for one thread
    process to run then moves onto the next thread, ie waits for the value to be loaded
    added and then stored before allowing other thread to jump in, helps reduce 
    concurrency errors*/

    pthread_create(&one,NULL,&sum1,NULL);/*creates the threads to run from*/
    pthread_create(&two,NULL,&sum2,NULL);

    pthread_join(one,NULL);/*ensure that the program doesnt end until threads have */
    pthread_join(two,NULL);/*finished running*/

    printf("Total --> %ld\n",total);

    return 0;
}