#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    char msg[100];
    if(pipe(pipefd) == -1){
        perror("pipe error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
        exit(1);
    }
    if(pid == 0){
        close(pipefd[1]);
        read(pipefd[0], msg, sizeof(msg));
        printf("Child: %s", msg);
        close(pipefd[0]);
    }
    else{
        close(pipefd[0]);
        printf("Enter msg: ");
        fgets(msg, sizeof(msg), stdin);
        write(pipefd[1], msg, sizeof(msg));
        close(pipefd[1]);
        wait(NULL);
    }
    return 0;
}