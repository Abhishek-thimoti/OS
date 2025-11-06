#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int bt; // Burst Time
    int pr; // Priority (Lower number = Higher priority)
    int wt; 
    int tat;
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void findAvgTime(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    
    // Sort processes based on Priority (ascending order of pr value)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort by priority (lower number first)
            if (p[i].pr > p[j].pr) {
                swap(&p[i], &p[j]);
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time (FCFS on sorted processes)
    p[0].wt = 0;
    p[0].tat = p[0].bt;
    total_wt += p[0].wt;
    total_tat += p[0].tat;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].tat;
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].pr, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (BT Priority): ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].pr);
    }

    findAvgTime(p, n);
    return 0;
}
