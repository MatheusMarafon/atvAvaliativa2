#include <stdio.h>
#include <pthread.h>

pthread_barrier_t barrier;

void* tarefa(void* arg) {
    printf("Thread %ld esperando na barreira\n", (long)arg);
    pthread_barrier_wait(&barrier);
    printf("Thread %ld passou pela barreira\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[5];
    pthread_barrier_init(&barrier, NULL, 5);
    
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, tarefa, (void*)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}