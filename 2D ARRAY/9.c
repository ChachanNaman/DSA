
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