#include <stdio.h>
#include <stdlib.h>

#define MAX 50

// Structure to hold the process information
typedef struct {
    int process_id;  // Process ID
    int arrival_time;  // Arrival Time
    int burst_time;    // Burst Time (CPU time needed)
    int remaining_time; // Remaining Burst Time (for preemptive scheduling)
    int completion_time; // Completion Time
    int turn_around_time; // Turnaround Time = Completion Time - Arrival Time
    int waiting_time; // Waiting Time = Turnaround Time - Burst Time
} Process;

// Shortest Job First Preemptive Scheduling
void sjf_preemptive(Process processes[], int n) {
    int time = 0; // Current time
    int completed = 0; // To track how many processes have completed
    int min_index; // Index of the process with the minimum remaining burst time

    // Initialize remaining time for preemptive SJF
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nSJF (Preemptive) Scheduling:\n");
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    
    while (completed < n) {
        min_index = -1;
        int min_remaining_time = 9999;
        
        // Find the process with the minimum remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                min_index = i;
            }
        }
        
        // If no process is found to execute, increment time
        if (min_index == -1) {
            time++;
            continue;
        }
        
        // Execute the selected process
        processes[min_index].remaining_time--;
        time++;

        // If process is complete, calculate its completion time and mark it as completed
        if (processes[min_index].remaining_time == 0) {
            processes[min_index].completion_time = time;
            processes[min_index].turn_around_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turn_around_time - processes[min_index].burst_time;
            completed++;
        }
    }

    // Print the results
    float total_turnaround = 0, total_waiting = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
        total_turnaround += processes[i].turn_around_time;
        total_waiting += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}

// Round Robin Scheduling
void round_robin(Process processes[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    int i;
    
    // Create a queue for processes (we can use an array here)
    int queue[MAX];
    int front = 0, rear = 0;

    // Initialize remaining time for round robin
    for (i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nRound Robin Scheduling (Quantum = %d):\n", quantum);
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    processes[i].remaining_time -= quantum;
                    time += quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
                    completed++;
                }
            }
        }
    }

    // Print the results
    float total_turnaround = 0, total_waiting = 0;
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turn_around_time, processes[i].waiting_time);
        total_turnaround += processes[i].turn_around_time;
        total_waiting += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}

int main() {
    int n, quantum;
    Process processes[MAX];

    // Read number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input for each process
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    // Ask for time quantum for Round Robin
    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Run Shortest Job First (Preemptive)
    sjf_preemptive(processes, n);

    // Run Round Robin
    round_robin(processes, n, quantum);

    return 0;
}

