#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

pthread_mutex_t mutex;
pthread_mutex_t forks[NUM_PHILOSOPHERS];
int state[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* num);
void take_forks(int philosopher_number);
void put_forks(int philosopher_number);
void test(int philosopher_number);
void think(int philosopher_number);
void eat(int philosopher_number);

int main() {
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        state[i] = THINKING;
        pthread_create(&philosophers[i], NULL, philosopher, &i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

void* philosopher(void* num) {
    int philosopher_number = *(int*)num;

    while (1) {
        think(philosopher_number);
        take_forks(philosopher_number);
        eat(philosopher_number);
        put_forks(philosopher_number);
    }
}

void take_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", philosopher_number);
    test(philosopher_number);

    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&forks[philosopher_number]);
}

void put_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);

    state[philosopher_number] = THINKING;
    printf("Philosopher %d is THINKING\n", philosopher_number);
    test((philosopher_number + 4) % NUM_PHILOSOPHERS);
    test((philosopher_number + 1) % NUM_PHILOSOPHERS);

    pthread_mutex_unlock(&mutex);
}

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[(philosopher_number + 4) % NUM_PHILOSOPHERS] != EATING &&
        state[(philosopher_number + 1) % NUM_PHILOSOPHERS] != EATING) {
        state[philosopher_number] = EATING;
        printf("Philosopher %d is EATING\n", philosopher_number);
        pthread_mutex_unlock(&forks[philosopher_number]);
    }
}

void think(int philosopher_number) {
    printf("Philosopher %d is THINKING\n", philosopher_number);
    sleep(rand() % 5 + 1);
}

void eat(int philosopher_number) {
    printf("Philosopher %d is EATING\n", philosopher_number);
    sleep(rand() % 3 + 1);
}
