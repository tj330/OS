#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

sem_t forks[SIZE];
sem_t mutex;

void* philosopher(void* num) {
    int id = *(int*)num;

        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        if (id % 2 == 0) {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id + 1) % SIZE]);
        } else {
            sem_wait(&forks[(id + 1) % SIZE]);
            sem_wait(&forks[id]);
        }

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % SIZE]);
        printf("Philosopher %d finished eating and is thinking again\n", id);

    return NULL;
}


int main() {
    pthread_t philosophers[SIZE];
    int ids[SIZE];

    for (int i = 0; i < SIZE; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < SIZE; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < SIZE; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}