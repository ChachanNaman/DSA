// 1a  -> Simple Calculator

#!/bin/bash

i=1
while [ $i -eq 1 ]
do
    printf "Enter 1st number: "
    read x
    printf "Enter 2nd number: "
    read y

    echo "1 Addition"
    echo "2 Subtraction"
    echo "3 Multiplication"
    echo "4 Division"
    echo "5 Exit"
    printf "Enter your choice:"
    read c

case $c in
1) echo "`expr $x + $y`";;
2) echo "`expr $x - $y`";;
3) echo "`expr $x \* $y`";;
4) if [ $y -eq 0 ]
    then 
        echo "Denominator can't be 0"
    else      
        result=$(echo "scale=2; $x / $y" | bc)
        echo "$result"
    fi;;
5) exit 0;;
*) echo "Invalid input";;
esac
done

// 1b  -> File Operations

#!/bin/bash

mkdir dirOne
cd dirOne
mkdir dirTwo
cat > st.txt
cp st.txt st2.txt
mv st2.txt st3.txt
chmod 744 st3.txt
ls -l

// 2a  -> Sorting asscending in parent and descending in child process

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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

void main(){
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

// 2b -> Create a zombie process

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main(){
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

// 2c  -> Create an orphan process

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main(){
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

// 3  -> First Come First Serve Scheduling Algorithm

#include <stdio.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int st;
} process;

int main() {
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    process p[n];
    printf("Please Enter the processes in increasing order of arrival time!!!\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    p[0].st = p[0].at;
    p[0].ct = p[0].st + p[0].bt;
    p[0].tat = p[0].ct - p[0].at;
    p[0].wt = p[0].tat - p[0].bt;

    float totalTAT = p[0].tat;
    float totalWT = p[0].wt;

    for (int i = 1; i < n; i++) {
        if (p[i - 1].ct < p[i].at) p[i].st = p[i].at;
        else p[i].st = p[i - 1].ct;

        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nFCFS:\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage waiting time: %.4f\n", totalWT / n);
    printf("Average turn around time: %.4f\n", totalTAT / n);

    printf("\nGantt Chart: \n");
    printf("%d", p[0].st);
    for (int i = 0; i < n; i++) {
        printf(" - P%d - %d", p[i].pid, p[i].ct);
    }
    printf("\n");

    return 0;
}

// 4 -> Shortest Remaining Time First Scheduling Algorithm

#include <stdio.h>

typedef struct{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int st;
    int rt;
    int isCompleted;
} process;

int main(){
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    process p[n];

    printf("Please Enter the processes in increasing order of arrival time!!!\n");
    for(int i = 0; i < n; i++){
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].isCompleted = 0;
    }

    int completed = 0, current_time = 0, prev = -1;
    float totalTAT = 0, totalWT = 0;

    printf("\nGantt Chart:\n");
    while(completed < n){
        int idx = -1;
        int min_rt = 100000;

        for(int i = 0; i < n; i++){
            if(p[i].at <= current_time && !p[i].isCompleted && p[i].rt < min_rt && p[i].rt > 0){
                min_rt = p[i].rt;
                idx = i;
            }
        }
        if(idx == -1){
            current_time++;
        }
        else {
            if(prev != idx) printf("%d - P%d - ", current_time, p[idx].pid);

            if(p[idx].rt == p[idx].bt) p[idx].st = current_time;

            p[idx].rt--;
            current_time++;

            if(p[idx].rt == 0){
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].isCompleted = 1;
                totalTAT += p[idx].tat;
                totalWT += p[idx].wt;
                completed++;
            }
            prev = idx;
        }
    }
    printf("%d\n", current_time);

    printf("\nSRTF:\n");
    printf("PID\tAT\tBT\tST\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage waiting time: %.4f\n", totalWT / n);
    printf("Average turn around time: %.4f\n", totalTAT / n);
    return 0;
}

// 5 -> Pipe Communication

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

// 6  -> Reader Writer Problem

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t mutex, wrt;
int sharedvar = 99;
int readercount = 0;

void *reader(void *param) {
    int id = *((int *)param);
    sem_wait(&mutex);
    readercount++;
    if (readercount == 1) sem_wait(&wrt);
    sem_post(&mutex);
    printf("\nReader %d is reading sharedvar = %d", id, sharedvar);
    sem_wait(&mutex);
    readercount--;
    if (readercount == 0) sem_post(&wrt);
    sem_post(&mutex);
    printf("\nReader %d is done", id);
    return NULL;
}

void *writer(void *param) {
    int id = *((int *)param);
    printf("\nWriter %d is trying to enter", id);
    sem_wait(&wrt);
    printf("\nWriter %d has entered CS", id);
    sharedvar++;
    printf("\nWriter %d CHANGED sharedvar TO %d", id, sharedvar);
    sem_post(&wrt);
    printf("\nWriter %d is out of CS", id);
    return NULL;
}

int main() {
    int n, i;
    printf("Enter the number of readers/writers: ");
    scanf("%d", &n);
    pthread_t readers[n], writers[n];
    int ids[n];
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    for (i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }
    for (i = 0; i < n; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

// 7 -> Banker's Algorithm

#include <stdio.h>

void print_array(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void print_matrix(int rows, int cols, int mat[rows][cols]) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void safety_check(int avail[], int r, int p, int need[p][r], int alloc[p][r]) {
    int work[r], finish[p], safe[p], count = 0;

    for(int j = 0; j < r; j++) work[j] = avail[j];
    for(int i = 0; i < p; i++) finish[i] = 0;

    for(int k = 0; k < p; k++) {
        for(int i = 0; i < p; i++) {
            if(!finish[i]) {
                int can_proceed = 1;
                for(int j = 0; j < r; j++) {
                    if(need[i][j] > work[j]) {
                        can_proceed = 0;
                        break;
                    }
                }
                if(can_proceed) {
                    for(int j = 0; j < r; j++)
                        work[j] += alloc[i][j];
                    safe[count++] = i;
                    finish[i] = 1;
                }
            }
        }
    }

    if(count == p) {
        printf("System is in a SAFE state.\nSafe Sequence: ");
        print_array(safe, p);
    } else {
        printf("System is in an UNSAFE state! Deadlock possible.\n");
    }
}

int main() {
    int p, r;
    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    int total[r];
    printf("Enter total instances of each resource:\n");
    for(int i = 0; i < r; i++) scanf("%d", &total[i]);

    int alloc[p][r], max[p][r];
    printf("\nEnter allocation matrix:\n");
    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter maximum matrix:\n");
    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    int avail[r], need[p][r];
    for(int j = 0; j < r; j++) {
        int sum = 0;
        for(int i = 0; i < p; i++) sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    for(int i = 0; i < p; i++)
        for(int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nAvailable Resources: ");
    print_array(avail, r);

    printf("\nNeed Matrix:\n");
    print_matrix(p, r, need);

    safety_check(avail, r, p, need, alloc);

    while(1) {
        int opt;
        printf("\nRequest resources? (1 = Yes / 0 = No): ");
        scanf("%d", &opt);
        if(!opt) break;

        int proc;
        printf("Enter process number (0-%d): ", p-1);
        scanf("%d", &proc);

        for(int j = 0; j < r; j++) {
            int req;
            printf("Enter additional instances for R%d: ", j+1);
            scanf("%d", &req);
            alloc[proc][j] += req;
        }

        // Recalculate
        for(int j = 0; j < r; j++) {
            int sum = 0;
            for(int i = 0; i < p; i++) sum += alloc[i][j];
            avail[j] = total[j] - sum;
        }
        for(int i = 0; i < p; i++)
            for(int j = 0; j < r; j++)
                need[i][j] = max[i][j] - alloc[i][j];

        safety_check(avail, r, p, need, alloc);
    }

    return 0;
}

// 8   -> FIFO Page Replacement Algorithm

#include <stdio.h>
#include <stdbool.h>

int main(){
    int pages[30], frame[10];
    int n, f, pageFault = 0, next = 0;
    bool found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference set:\n");
    for (int i = 0; i < n; i++) {
        printf("Element[%d]: ", i);
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++) frame[i] = -1;

    printf("\nPage\tFrames\t\tPage Fault\n");
    for(int i = 0; i < n; i++){
        found = false;
        for(int j = 0; j < f; j++){
            if(pages[i] == frame[j]){
                found = true;
                break;
            }
        }
        if(!found){
            frame[next] = pages[i];
            next = (next + 1) % f;
            pageFault++;

            printf("%d\t", pages[i]);
            for(int k = 0; k < f; k++){
                if(frame[k] != -1) printf("%d ", frame[k]);
                else printf("- ");
            }
            printf("\t\tYes\n");
        }
        else{
            printf("%d\t", pages[i]);
            for(int k = 0; k < f; k++){
                if(frame[k] != -1) printf("%d ", frame[k]);
                else printf("- ");
            }
            printf("\t\tNo\n");
        }
              
    }
    printf("Page faults = %d\n", pageFault);
    return 0;
}

// 9 -> LRU Page Replacement Algorithm

#include <stdio.h>
#include <stdbool.h>

int main() {
    int pages[30], frame[10];
    int n, f, page_fault = 0;
    int recent[10];
    int time = 0;
    int found, min, replace_index;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        printf("Element[%d]: ", i);
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (int i = 0; i < f; i++) {
        frame[i] = -1;
        recent[i] = 0;
    }

    printf("\nPage\tFrames\t\tPage Fault\n");
    for (int i = 0; i < n; i++) {
        time++;
        found = false;

        for(int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                recent[j] = time;
                break;
            }
        }
        if(!found){
            bool empty_found = false;
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    recent[j] = time;
                    page_fault++;
                    empty_found = true;
                    break;
                }
            }
            if(!empty_found) {
                min = recent[0];
                replace_index = 0;
                for (int k = 1; k < f; k++) {
                    if (recent[k] < min) {
                        min = recent[k];
                        replace_index = k;
                    }
                }
                frame[replace_index] = pages[i];
                recent[replace_index] = time;
                page_fault++;
            }
            printf("%d\t", pages[i]);
            for (int k = 0; k < f; k++) {
                if (frame[k] != -1)
                    printf("%d ", frame[k]);
                else
                    printf("- ");
            }
            printf("\t\tYes\n");

        } 
        else{
            printf("%d\t", pages[i]);
            for (int k = 0; k < f; k++) {
                if (frame[k] != -1)
                    printf("%d ", frame[k]);
                else
                    printf("- ");
            }
            printf("\t\tNo\n");
        }
    }
    printf("\nTotal Page Faults = %d\n", page_fault);
    return 0;
}