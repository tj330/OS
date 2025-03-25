#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full; 
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        item++;
        sem_wait(&empty);  // Decrease empty count
        pthread_mutex_lock(&mutex);

        // Produce item
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);   // Increase full count
        sleep(1);          // Simulate production time
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Decrease full count
        pthread_mutex_lock(&mutex);

        // Consume item
        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  // Increase empty count
        sleep(1);          // Simulate consumption time
    }
}

int main() {
    pthread_t prodThread, consThread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    // Join threads (infinite loop in this case)
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
