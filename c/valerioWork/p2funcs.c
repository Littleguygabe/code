#include <stdio.h>

void printArray(int * arr, int length);
void bubble_sort(int *arr, int n);
int main (int argc, char *argv[]) {
    
    /*sorting algs // pointers to functions*/

    int arr[10] = {10,9,8,7,6,5,4,3,2,1};


    bubble_sort(arr,10);
    printArray(arr,10);


    return 0;
}

void printArray(int * arr,int length){
    int i;
    for (i=0;i<length;i++){
        printf("%d,",arr[i]);
    }
}

void bubble_sort(int *arr, int n){
    int i,j;
    int tmp;
    for (i=0;i<(n-1);i++){
        for (j=i+1;j<n;j++){ /*j starts from i as there is no need to check if the elements before arr[i] are sorted as they must be sorted due to the nature of bubble sort*/
            if (arr[j]<arr[i]){
                tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp; /*runs through every element in the list checking the bubble
                                then if the next element is bigger than the current element then swap them around*/
            }
        }
    }
}

