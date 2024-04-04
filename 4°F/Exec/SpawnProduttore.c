#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BLOCK_DIM 1024

#define PROGRAM "./consumatore.sh"

int spawn(char program[], char *argument[]) // il suo PC punta al figlio. Program Counter del padre punta al figlio
{
    int p;
    printf("Sono il padre, PID: %d", getpid()); // pid figlio = pid consumatore

    p = fork();

    if (p < 0)
    {
        printf("Errore fork");
        return -1;
    }

    if (p > 0)
    {
        printf("Sono il padre, PID: %d", getpid()); // pid figlio = pid consumatore
        return 0;                                   // success code
    }

    if (p = 0)
    {
        printf("Sono il figlio, PID: %d", getpid()); // pid figlio = pid consumatore, il figlio vienen passato a un altro programma
    }

    execv(program, argument); // rispetto alla execl, invece di mettere i parametri passo un vettore
    // program è una stringa, argument è un array di stringhe; | Program é "./consumatore.sh", cioè il percorso del file da eseguire
    printf("\nErrore execv");
    abort();
}

int main(int argc, char *argv[]) // ./produttore.sh fileOrigine.txt fileDestinazione.txt
{
    FILE *file;
    int fifo;
    unsigned char buffer[BLOCK_DIM];
    int n;
    char *arg[3]; // array di puntatori a carattere, contiene tre stringhe; parametri da passare all'execl
    int a;

    printf("\nProcesso produttore - padre, PID: %d", getpid());
    if (argc != 3)
    {
        printf("Per mandare in esecuzione produttore.exe ");
        return 0;
    }

    // ./consumatore.sh destinazione.txt NULL

    arg[0] = (char *)malloc(strlen(PROGRAM) + 1); // strlen va incrementato di uno sennò perde il terminatore, questo è lo spazio di memoria allocato per immagazzinare l'indirizzo di program
    strcpy(arg[0], PROGRAM);

    arg[1] = (char *)malloc(strlen(argv[2]) + 1); // nome del file, terminatore incluso
    strcpy(arg[1], argv[2]);

    arg[2] = NULL;

    if (spawn(PROGRAM, arg) < 0) // spawn() --> funzione che crea un processo
    {
        printf("Errore spawn");
        free(arg[0]); // si libera lo heap
        free(arg[1]);
        exit(-2);
    }

    printf("\narg[0] = %s \n", arg[0]); // controllo se è ./consumatore.sh

    // creazione fifo
    if (mkfifo("my_fifo", 0777) < 0)
    {
        if (errno != EEXIST)
        {
            printf("\nErrore creazione fifo");
        }
        return 0;
    }

    fifo = open("my_fifo", O_WRONLY);

    if (fifo < 0)
    {
        printf("\nErrore apertura fifo");
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    file = fopen(argv[1], "rb");

    if (file = NULL)
    {
        printf("Errore apertura file");
        free(arg[0]);
        free(arg[1]);
        close(fifo);
        return 0;
    }

    while (!feof(file))
    {
    }
}