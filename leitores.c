#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int leitores = 0;

void* leitor(void* arg) {
    pthread_mutex_lock(&mutex);
    leitores++;
    if (leitores == 1) {
        // Bloquear escritor
    }
    pthread_mutex_unlock(&mutex);

    // Ler o recurso
    printf("Leitor %ld lendo\n", (long)arg);

    pthread_mutex_lock(&mutex);
    leitores--;
    if (leitores == 0) {
        // Liberar escritor
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* escritor(void* arg) {
    // Esperar se houver leitores
    printf("Escritor %ld escrevendo\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[5];
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, (i % 2 == 0) ? escritor : leitor, (void*)i);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
