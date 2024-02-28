#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUMERO 2
int main(int argc, char *argv[])
{
    // padre passa al figlio dati inseriti da utente per stamparli

    typedef struct
    {
        char nome[20];
        char cognome[20];
        float media;
    } Studente;

    int p;
    int fd[2];

    // apertura pipe
    if (pipe(fd) < 0)
    {
        printf("Errore pipe \n");
        exit(-1);
    }

    // creazione fork
    p = fork();

    if (p < 0)
    {
        printf("ERRORE creazione fork \n");
        exit(-1);
    }

    if (p == 0)
    {
        // figlio
        Studente array[NUMERO];

        // chiuso scrittura
        close(fd[1]);

        // lettura pipe
        read(fd[0], array, sizeof(array));

        // stampa dati
        for (int i = 0; i < NUMERO; i++)
        {
            printf("nome %s  \n", array[i].nome);
            printf("cognome %s \n", array[i].cognome);
            printf("media %.2f \n", array[i].media);
        }

        // chiusura pipe
        close(fd[0]);
    }
    else
    {
        // padre
        Studente array[NUMERO];

        // chiusra pipe lettura
        close(fd[0]);

        // inserimento dati
        for (int i = 0; i < NUMERO; i++)
        {
            printf("Inserire nome \n");
            scanf("%s", array[i].nome);
            printf("Inserire cognome \n");
            scanf("%s", array[i].cognome);
            printf("Inserire media \n");
            scanf("%f", &array[i].media);
        }

        // scrittura dati su pipe
        write(fd[1], array, sizeof(array));

        // chiusura pipe
        close(fd[1]);
    }

    return 0;
}