// 2a  -> Sorting asscending in parent and descending in child process

#include <stdio.h>
#include <sys/types.h>  //Contains data types (like pid_t) used for process IDs.
#include <unistd.h>     //Contains the fork() and getpid() functions used for creating processes.
#include <stdlib.h>     //Contains exit() function used to safely end the program.
#include <sys/wait.h>   //Contains wait() function used to wait for process termination.

void displayArr(int arr[], int n){
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void sortAscending(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Sorted in Ascending Order (Parent): ");
    displayArr(arr, n);
}

void sortDescending(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] < arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Sorted in Descending Order (Child): ");
    displayArr(arr, n);
}

int main(){
    int n;
    printf("Enter no of elements: ");
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++){
        printf("Enter element %d: ",i + 1);
        scanf("%d", &arr[i]);
    }
    pid_t num_pid = fork();
    if(num_pid == 0){
        printf("This is Child process with pid = %d\n", getpid());
        sortDescending(arr, n);
    }
    else if(num_pid > 0){
        printf("This is Parent process with pid = %d\n", getpid());
        sortAscending(arr, n);
    }
    else{
        perror("fork");
    }
    exit(0);
}