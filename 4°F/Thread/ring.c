#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_DIM  2048
char buffer[BUFFER_DIM];

struct ThreadArgs {
    char* filename;
    size_t size;
};

void* leggi(void* par)
{
    struct ThreadArgs* args = (struct ThreadArgs*)par;
    FILE *sorgente = fopen(args->filename, "r");
    if (sorgente == NULL)
    {
        perror("Errore nell'apertura del file sorgente");
        pthread_exit(NULL);
    }

    size_t n = fread(buffer, 1, BUFFER_DIM, sorgente);
    fclose(sorgente);

    pthread_exit((void*)n);
}

void* scrivi(void* par)
{
    struct ThreadArgs* args = (struct ThreadArgs*)par;
    FILE *destinazione = fopen(args->filename, "w");
    if (destinazione == NULL)
    {
        perror("Errore nell'apertura del file destinazione");
        pthread_exit(NULL);
    }

    if (fwrite(buffer, 1, args->size, destinazione) != args->size)
    {
        perror("Errore nella scrittura sul file destinazione");
        fclose(destinazione);
        pthread_exit(NULL);
    }

    fclose(destinazione);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <file_sorgente> <file_destinazione>\n", argv[0]);
        return 1;
    }

    pthread_t t1, t2;
    void *result;

    struct ThreadArgs args_leggi = { argv[1], 0 };
    pthread_create(&t1, NULL, &leggi, (void*)&args_leggi);

    pthread_join(t1, &result);
    size_t n = (size_t)result;
    if (n == 0)
    {
        printf("Errore durante la lettura del file sorgente.\n");
        return 2;
    }

    struct ThreadArgs args_scrivi = { argv[2], n };
    pthread_create(&t2, NULL, &scrivi, (void*)&args_scrivi);

    pthread_join(t2, NULL);

    return 0;
}
