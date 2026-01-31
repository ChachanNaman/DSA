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
