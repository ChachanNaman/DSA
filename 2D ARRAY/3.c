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