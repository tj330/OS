#include <stdio.h>

#define MAX 10

struct Process {
    int pid, at, bt, rt, priority, ct, tat, wt;
};

void preemptivePriority(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    int gantt[MAX * 10], ganttTime[MAX * 10], ganttSize = 0;

    while (completed < n) {
        minIndex = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            time++;
            continue;
        }

        if (ganttSize == 0 || gantt[ganttSize - 1] != p[minIndex].pid) {
            gantt[ganttSize] = p[minIndex].pid;
            ganttTime[ganttSize] = time;
            ganttSize++;
        }

        p[minIndex].rt--;
        time++;

        if (p[minIndex].rt == 0) {
            p[minIndex].ct = time;
            p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
            p[minIndex].wt = p[minIndex].tat - p[minIndex].bt;
            completed++;
        }
    }

    // Print Process Table
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nAvg TAT: %.2f\n", totalTAT / n);
    printf("Avg WT: %.2f\n", totalWT / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < ganttSize; i++) {
        printf("| P%d ", gantt[i]);
    }

    printf("|\n");

    for (int i = 0; i < ganttSize; i++) {
        printf("%d   ", ganttTime[i]);
    }
    printf("%d\n", time);
}

int main() {
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, and Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
    }

    preemptivePriority(p, n);
    return 0;
}
