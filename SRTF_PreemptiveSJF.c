#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Note: This implementation assumes processes are entered in order of arrival time.
// A more robust version would sort them by arrival time first.

struct Process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Remaining Time
    int ct; // Completion Time
};

void findAvgTime(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    int completed_processes = 0;
    int current_time = 0;
    
    // Copy Burst Time to Remaining Time
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }

    while (completed_processes < n) {
        int shortest_job_index = -1;
        int min_remaining_time = INT_MAX;

        // Find the process with the shortest remaining time available at current_time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_remaining_time) {
                    min_remaining_time = p[i].rt;
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1) {
            // CPU is idle, advance time
            current_time++;
            continue;
        }

        // Execute the selected process for one time unit
        p[shortest_job_index].rt--;
        current_time++;

        // Check if the process completed its execution
        if (p[shortest_job_index].rt == 0) {
            p[shortest_job_index].ct = current_time;
            completed_processes++;
            
            // Calculate TAT and WT for the completed process
            p[shortest_job_index].tat = p[shortest_job_index].ct - p[shortest_job_index].at;
            p[shortest_job_index].wt = p[shortest_job_index].tat - p[shortest_job_index].bt;
            
            total_wt += p[shortest_job_index].wt;
            total_tat += p[shortest_job_index].tat;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d (AT BT): ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    findAvgTime(p, n);
    return 0;
}
