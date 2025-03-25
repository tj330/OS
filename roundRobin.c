#include <stdio.h>

struct p {
    int id;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

int main() {
    int n, quantum, id = 0;
    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    printf("Enter the quanta:\n");
    scanf("%d", &quantum);
    
    struct p process[n];
    printf("Enter the details of the process (AT BT):\n");
    
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        process[i].id = i + 1;
        scanf("%d%d", &process[i].at, &process[i].bt);
        process[i].rt = process[i].bt;
    }

    int completed = 0, time = 0;
    int executetime;

    // Gantt chart with timestamps
    int gantt_process[1000];
    int gantt_time[1000];
    int gantt_index = 0;

    while (completed < n) {
        int done_in_this_round = 0;

        for (int i = 0; i < n; i++) {
            if (process[i].rt > 0 && process[i].at <= time) {
                if (gantt_index == 0 || gantt_process[gantt_index - 1] != process[i].id) {
                    gantt_process[gantt_index] = process[i].id;
                    gantt_time[gantt_index] = time;
                    gantt_index++;
                }

                executetime = (quantum < process[i].rt) ? quantum : process[i].rt;
                time += executetime;
                process[i].rt -= executetime;

                if (process[i].rt == 0) {
                    completed++;
                    process[i].tat = time - process[i].at;
                    process[i].wt = process[i].tat - process[i].bt;
                }
                done_in_this_round = 1;
            }
        }
        if (!done_in_this_round) {
            time++;
        }
    }

    // Print the Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < gantt_index; i++) {
        printf("| P%d ", gantt_process[i]);
    }
    printf("|\n");

    for (int i = 0; i < gantt_index; i++) {
        printf("%d   ", gantt_time[i]);
    }
    printf("%d\n", time);

    // Print process information
    printf("\nID\tAT\tBT\tWT\tTAT\n");
    float t_wt = 0, t_tat = 0;

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", process[i].id, process[i].at, process[i].bt, process[i].wt, process[i].tat);
        t_wt += process[i].wt;
        t_tat += process[i].tat;
    }

    printf("Average Waiting time: %.2f\n", t_wt / n);
    printf("Average Turnaround time: %.2f\n", t_tat / n);

    return 0;
}
