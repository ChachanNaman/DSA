#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter the number of processes\n");
    scanf("%d", &n);

    printf("Enter the number of resource types\n");
    scanf("%d", &m);

    int available[m], max[n][m], allocation[n][m], need[n][m];

    // Input available resources
    for (int i = 0; i < m; i++) {
        printf("available[%d] = ", i);
        scanf("%d", &available[i]);
    }

    // Input maximum resources for each process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("max[%d][%d] = ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocated resources for each process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("allocation[%d][%d] = ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int work[m];
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    
    int safeSeq[n], count = 0;
    bool found;

    // Safety algorithm
    while (count < n) {
        found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");
    return 0;
}