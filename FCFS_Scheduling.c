#include <stdio.h>

void findAvgTime(int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculate waiting time (WT)
    for (int i = 1; i < n; i++) {
        // WT[i] = BT[i-1] + WT[i-1]
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    // Calculate turnaround time (TAT) and total times
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n];
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    findAvgTime(n, bt);
    return 0;
}
