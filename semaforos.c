#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* produtor(void* arg) {
    sem_wait(&sem); // Esperar por um espaço
    printf("Produto produzido\n");
    sem_post(&sem); // Liberar o semáforo
    return NULL;
}

void* consumidor(void* arg) {
    sem_wait(&sem); // Esperar por um produto
    printf("Produto consumido\n");
    sem_post(&sem); // Liberar o semáforo
    return NULL;
}

int main() {
    pthread_t threads[4];
    sem_init(&sem, 0, 1); // Inicializa o semáforo

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, produtor, NULL);
        pthread_create(&threads[i + 2], NULL, consumidor, NULL);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem); // Destruir semáforo
    return 0;
}
