#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p, p2, p3; // variabile intera per gestire processo padre e figlio
               // PID del padre == PID figlio, mentre PID figlio == 0

int main(int argc, char *argv[])
{
    p = fork(); // padre genera un processo figlio --> genera un processo (il processo originale è Main)

    if (p)
    {
        p2 = fork();
        if (p2)
        {
            p3 = fork();
            if (p3)
            {
                printf("Processo padre, p: %d, PID: %d, PID processo generatore(bash ./): %d\n", p, getpid(), getppid()); // p del padre == PID del figlio
                return 0;
            }
        }
    }
    if (!p)
    {
        printf("Processo figlio1, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
        return 0;
    }
    if (!p2)
    {
        printf("Processo figlio2, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
        return 0;
    }

    printf("Processo figlio3, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
    return 0;
}