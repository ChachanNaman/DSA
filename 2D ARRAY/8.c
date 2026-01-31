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
