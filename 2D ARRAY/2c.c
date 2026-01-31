#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t num_pid = fork();
    if(num_pid > 0){
        printf("This is Parent process of id: %d\n", getpid());
        printf("Child process id: %d\n", num_pid);
    }
    else if(num_pid == 0){
        sleep(10);
        printf("This is child process of id: %d\n", getpid());
        printf("This is parent process of id: %d\n", getppid());
    }
    exit(0);
}
