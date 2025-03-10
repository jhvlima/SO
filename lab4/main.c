#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ADDS 24
#define NUM_THREADS 3

int buffer = 0;
pthread_mutex_t mutex;
int counts[NUM_THREADS] = {0};

void printThread()
{
    printf("TID: %lu PID: %d Buffer: %d\n", (unsigned long)pthread_self(), getpid(), buffer);
}

void *add(void *arg)
{
    int thread_id = *(int *)arg;
    while (buffer < NUM_ADDS) // enquanto não acabou a contagem
    {
        sleep(1);
        pthread_mutex_lock(&mutex);
        if (buffer >= NUM_ADDS) // acabou a contagem e não pode adicionar mais
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printThread();
        buffer++;
        counts[thread_id]++;
        pthread_mutex_unlock(&mutex);
    }
    printf("TID %lu worked on the buffer %d times\n",  (unsigned long)pthread_self(), counts[thread_id]);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Criar threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, add, &thread_ids[i]);
    }

    // Esperar todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Total buffer accesses: %d\n", buffer);

    pthread_mutex_destroy(&mutex);
    return 0;
}