#include <stdio.h>

void findAvgTime(int n, int at[], int bt[], int quantum) {
    int rt[n]; // Remaining Time
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;
    int current_time = 0;
    int completed_processes = 0;
    
    // Copy Burst Time to Remaining Time
    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }
    
    // Simplified logic: assumes processes are already ordered by arrival time (AT).
    // The main loop implements the round robin cycle.
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                int execute_time = (rt[i] < quantum) ? rt[i] : quantum;
                
                // Execute for 'execute_time'
                current_time += execute_time;
                rt[i] -= execute_time;
                
                // Check for completion
                if (rt[i] == 0) {
                    completed_processes++;
                    
                    // TAT = Completion Time (current_time) - Arrival Time
                    tat[i] = current_time - at[i];
                    // WT = TAT - Burst Time
                    wt[i] = tat[i] - bt[i];
                    
                    total_wt += wt[i];
                    total_tat += tat[i];
                }
            }
        }
    }

    printf("\nProcess\tAT\tBT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int at[n], bt[n];
    printf("Enter Arrival Time (AT) and Burst Time (BT) for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d (AT BT): ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }
    
    // Note: For simplicity, the AT array is used, but the code doesn't actively sort or manage the ready queue based on AT 
    // in a full preemptive way; it cycles through the initial process list.
    findAvgTime(n, at, bt, quantum);
    return 0;
}
