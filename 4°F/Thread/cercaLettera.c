/*Creare un programma in C che legge le prime 32 lettere di un file di testo e stampa la lettera inserita dall'utente per ogni occorrenza (Es: se l'utente inserisce la lettera 'a' e questa si trova 2 volte
nelle 32 lettere il programma dovrà stampare a video: 
'trovata la lettera a
trovata la lettera a'
La lettura dei dati dal file deve essere fatta con un thread, mentre la ricerca della lettera tra i dati letti deve essere fatta tramite quattro thread con carico bilanciato
)*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4
#define BUFFER_SIZE 32

typedef struct {
    char *buffer;
    char target;
    int start;
    int end;
} ThreadData;

void *read_file(void *filename) {
    static char buffer[BUFFER_SIZE + 1];
    FILE *file = fopen((char *)filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}

void *search_letter(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i < data->end; i++) {
        if (data->buffer[i] == data->target) {
            printf("Trovata la lettera %c\n", data->target);
        }
    }
    return NULL;
}

int main() {
    char filename[256];
    char target;
    char *buffer;
    pthread_t read_thread;
    pthread_t search_threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Input del nome del file e della lettera da cercare
    printf("Inserisci il nome del file: ");
    scanf("%255s", filename);
    printf("Inserisci la lettera da cercare: ");
    scanf(" %c", &target);

    // Creazione del thread per leggere il file
    if (pthread_create(&read_thread, NULL, read_file, filename) != 0) {
        perror("Failed to create read thread");
        exit(EXIT_FAILURE);
    }

    // Attendere la lettura del file
    if (pthread_join(read_thread, (void **)&buffer) != 0) {
        perror("Failed to join read thread");
        exit(EXIT_FAILURE);
    }

    // Configurazione dei dati per i thread di ricerca
    int segment_size = BUFFER_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].buffer = buffer;
        thread_data[i].target = target;
        thread_data[i].start = i * segment_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? BUFFER_SIZE : (i + 1) * segment_size;
    }

    // Creazione dei thread di ricerca
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&search_threads[i], NULL, search_letter, &thread_data[i]) != 0) {
            perror("Failed to create search thread");
            exit(EXIT_FAILURE);
        }
    }

    // Attendere il completamento dei thread di ricerca
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(search_threads[i], NULL) != 0) {
            perror("Failed to join search thread");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
