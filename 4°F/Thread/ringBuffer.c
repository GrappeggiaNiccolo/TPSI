#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define BUFFER_DIM 1024

unsigned char buffer[BUFFER_DIM];
int n = 0;
bool eof = false;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// lettura dei dati da file
void* leggi(void *arg)
{
    FILE *file = (FILE *)arg;
    while (!feof(file))
    {
        pthread_mutex_lock(&mutex);
        n = fread(buffer, 1, BUFFER_DIM, file);
        if (n < BUFFER_DIM) {
            eof = true;
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    eof = true;
    pthread_cond_signal(&cond); // Segnale finale per sbloccarsi in caso di EOF
    return NULL;
}

// scrittura dei dati su file
void* scrivi(void *arg)
{
    FILE *file = (FILE *)arg;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        while (n == 0 && !eof)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        if (n > 0)
        {
            fwrite(buffer, 1, n, file);
            n = 0; // Reset n after writing
        }
        pthread_mutex_unlock(&mutex);
        if (eof && n == 0)
        {
            break;
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    FILE *origine, *destinazione;
    pthread_t thread_lettura, thread_scrittura;

    if (argc != 3)
    {
        printf("Uso: %s file-origine file-destinazione\n", argv[0]);
        return 0;
    }

    // apertura in lettura del file di origine
    origine = fopen(argv[1], "rb");
    if (origine == NULL)
    {
        printf("Errore apertura file %s\n", argv[1]);
        return 0;
    }

    // apertura in scrittura del file di destinazione
    destinazione = fopen(argv[2], "wb");
    if (destinazione == NULL)
    {
        printf("Errore apertura file %s\n", argv[2]);
        fclose(origine);
        return 0;
    }

    // esecuzione dei thread di lettura e scrittura
    pthread_create(&thread_lettura, NULL, leggi, (void *)origine);
    pthread_create(&thread_scrittura, NULL, scrivi, (void *)destinazione);

    // attesa della conclusione dei thread e chiusura dei file
    pthread_join(thread_lettura, NULL);
    pthread_join(thread_scrittura, NULL);

    fclose(origine);
    fclose(destinazione);

    return 0;
}
