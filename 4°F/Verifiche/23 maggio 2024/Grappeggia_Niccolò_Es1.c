// Niccolò Grappeggia - Fila A
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DIM 32
// Variabii condivise
unsigned char buffer[DIM];
FILE *file;

void *Lettura(void *arg)
{
    char c;
    // popolo l'array
    for (int i = 0; i < 32; i++)
    {
        c = fgetc(file);
        // printf("char: %c\n", c);
        buffer[i] = c;
    }

    // Chiusura file e thread
    fclose(file);
    pthread_exit(NULL);
}

void *Ricerca(void *arg)
{
    // Distinguo i thread in base al numero che viene passato alla funzione
    int id = *(int *)arg;
    switch (id)
    {
    case 1:
        // thread 1
    // non finito, arrivato qui
        break;
    }
}

int main(int argc, char *argv[])
{

    // Inizializzazione variabili
    pthread_t TLettura, TRicerca1, TRicerca2, TRicerca3, TRicerca4;
    int arrayId[4];
    file = fopen("file.txt", "r");
    // popolo l'array con i numeri identificativi dei thread
    for (int i = 0; i < 4; i++)
    {
        arrayId[i] = i + 1;
    }

    // Creazione thread
    pthread_create(&TLettura, NULL, &Lettura, NULL);
    pthread_create(&TRicerca1, NULL, &Ricerca, (void *)arrayId[0]);
    pthread_create(&TRicerca2, NULL, &Ricerca, (void *)arrayId[1]);
    pthread_create(&TRicerca3, NULL, &Ricerca, (void *)arrayId[2]);
    pthread_create(&TRicerca4, NULL, &Ricerca, (void *)arrayId[3]);
    // Chiusura thread
    pthread_join(TLettura, NULL);
    pthread_join(TRicerca1, NULL);
    pthread_join(TRicerca2, NULL);
    pthread_join(TRicerca3, NULL);
    pthread_join(TRicerca4, NULL);
}
