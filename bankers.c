#include <stdio.h>
#define P 5
#define R 3

int available[R];
int max[P][R];
int allocation[P][R];
int need[P][R];
int safeSequence[P];

int isSafeState() {
    int work[R];
    int finish[P] = {0};
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    while (count < P) {
        int found = 0;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;

                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                    break;
                }

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];
                        safeSequence[count++] = i;
                        finish[i] = 1;
                        found = 1;
                    }
            }
        }
        if (!found) {
            return 0;
        }
    
    }
    
    return 1;
}

void printMatrix(int matrix[P][R], char* title) {
    printf("\n%s:\n", title);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void requestResources() {
    int process, request[R];

    printf("\nEnter process number requesting resources (0-%d): ", P - 1);
    scanf("%d", &process);

    printf("Enter requested resources for process %d: ", process);

    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }


    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
    }


    for (int i = 0; i < R; i++) {
        if (request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];

    }
    
    if (isSafeState()) {
        printf("Request granted. System remains in a safe state.\n");
    } else {
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request denied. System would enter an unsafe state.\n");
    }
}
int main() {
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }
    
    printf("Enter maximum resource demand matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    
    printf("Enter allocated resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    
    
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    
    printMatrix(max, "Maximum Demand Matrix");
    printMatrix(allocation, "Allocated Resources Matrix");
    printMatrix(need, "Final Need Matrix");

    if (isSafeState()) {
        printf("\nSystem is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < P; i++) {
            printf("%d ", safeSequence[i]);
        }
        
        printf("\n");
    } else {
        printf("\nSystem is in an unsafe state. Deadlock may occur!\n");
    }

    requestResources();
    
    return 0;
}