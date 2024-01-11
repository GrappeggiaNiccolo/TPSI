#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int p;

int status;

int main(int argc, char *argv[])
{
    int lunghezza = 3, numeri[lunghezza];
    printf("Inserire 3 numeri: \n");
    for (int i = 0; i < lunghezza; i++)
    {
        printf("Inserire %d° numero", i + 1);
        scanf("%d", &numeri[i]);
        if (numeri[i] < 0 || numeri[i] > 20)
        {
            printf("numero non valido");
            i--;
        }
    }

    p = fork();

    if (p != 0) // processo padre
    {
        printf("Processo padre, p: %d, PID: %d\n", p, getpid());
        printf("Wait (PID figlio): %d\n", wait(&status)); // aspetta che il figlio finisca/muoia
        printf("Somma del figlio = %d\n", WEXITSTATUS(status));
    }
    else // processo figlio, p è == 0
    {
        printf("Processo figlio, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());

        int somma = numeri[0] + numeri[1];
        exit(somma);
    }
    return 0;
}