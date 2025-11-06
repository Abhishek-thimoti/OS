#include <stdio.h>
#include <stdlib.h>

// Structure to hold process details
struct Process {
    int pid;
    int bt; // Burst Time
    int wt; // Waiting Time
    int tat; // Turnaround Time
};

void findAvgTime(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    
    // Sort processes based on burst time (ascending order)
    // This is the core logic of non-preemptive SJF
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time
    p[0].wt = 0;
    p[0].tat = p[0].bt;
    total_wt += p[0].wt;
    total_tat += p[0].tat;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].tat; // WT = Completion Time of previous process - Arrival Time (assumed 0)
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    findAvgTime(p, n);
    return 0;
}
