def calculate_fifo_times(processes):
    """
    Calculates waiting and turnaround times for FCFS scheduling.
    processes: List of (process_id, burst_time) tuples.
    """
    n = len(processes)
    completion_time = 0
    waiting_time_total = 0
    turnaround_time_total = 0
    
    print("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time")
    
    for i in range(n):
        pid, burst_time = processes[i]
        
        # Completion Time = Time when CPU finishes executing the process
        completion_time += burst_time
        
        # Turnaround Time = Completion Time - Arrival Time (assuming Arrival Time = 0)
        turnaround_time = completion_time
        
        # Waiting Time = Turnaround Time - Burst Time
        waiting_time = turnaround_time - burst_time
        
        waiting_time_total += waiting_time
        turnaround_time_total += turnaround_time
        
        print(f"P{pid}\t{burst_time}\t\t{waiting_time}\t\t{turnaround_time}")

    print("\n--- Averages ---")
    print(f"Average Waiting Time: {waiting_time_total / n:.2f}")
    print(f"Average Turnaround Time: {turnaround_time_total / n:.2f}")

# Example Usage: (Process ID, Burst Time)
process_data = [
    (1, 10),
    (2, 5),
    (3, 8)
]

print("--- FCFS (FIFO) Scheduling Simulation ---")
calculate_fifo_times(process_data)
