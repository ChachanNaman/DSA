#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t num_pid = fork();
    if(num_pid < 0) printf("Error\n");
    else if(num_pid == 0){
        printf("This is child process of id: %d\n", getpid());
    }
    else{
        sleep(10);
        printf("Parent->");
        system("ps -axj | tail");
    }
    exit(0);
}

