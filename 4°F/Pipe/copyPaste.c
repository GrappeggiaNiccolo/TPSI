#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Creare un programma C che effettua la copia di un file;
// il programma è composto da due distinti processi, il padre(che legge blocchi di dati dal file di origine e li inserisce in una pipe)
// e il figlio( che estrae i dati dalla pipe e li scrive nel file di destinazione).

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int p, status, fd[2];

    if (pipe(fd)) // creazione pipe
    {
        printf("Errore di generazione pipe");
        return -1;
    }

    p = fork();

    if (p < 0)
    {
        printf("ERRORE FORK");
        return -1;
    }

    if (!p)
    { // Processo figlio
        printf("Processo figlio, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
        char buffer[BUFFER_SIZE];
        
        close(fd[1]); // figlio chiude la scrittura

        exit(0);
    }
    // processo padre
    printf("Processo padre, p: %d, PID: %d\n", p, getpid());

    close(fd[0]); // padre chiude la lettura

    const char *messaggio = "Cruo";
    if (write(fd[1], messaggio, strlen(messaggio)) == -1)
    {
        printf("Errore Pipe");
        exit(-1);
    }

    close(fd[1]); // padre chiude la scrittura

    printf("\nWait (PID figlio): %d\n", wait(&status)); // aspetta che il figlio finisca/muoia
}