#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
// passare al p figlio una stringa con pipe

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int p, fd[2]; // fd = File Descriptor
    int status;

    if (pipe(fd)) // creazione pipe
    {
        printf("Errore di generazione pipe");
        return -1;
    }
    p = fork();

    if (p < 0)
    {
        printf("ERRORE FORK");
    }

    if (!p) // processo figlio
    {
        printf("Processo figlio, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
        char buffer[BUFFER_SIZE];

        close(fd[1]); // figlio chiude la scrittura
        
        int n = read(fd[0], buffer, BUFFER_SIZE);   // Il figlio aspetta di leggere qualcosa finché non la trova
        if (n == -1)
        {
            printf("ERRORE LETTURA PIPE");
            exit(-1);
        }

        buffer[n] = '\0';
        printf("Messaggio: %s", buffer);

        close(fd[0]); // figlio chiude la lettura
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
    return 0;
}