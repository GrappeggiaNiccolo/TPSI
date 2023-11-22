#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p; // variabile intera per gestire processo padre e figlio
       // PID del padre == PID figlio, mentre PID figlio == 0
int p2;

int main(int argc, char *argv[])
{
    p = fork(); // padre genera un processo figlio --> genera un processo (il processo originale è Main)


    if (p) // processo padre
    {
        printf("Processo padre, p: %d, PID: %d, PID processo generatore(bash ./): %d\n", p, getpid(), getppid()); // p del padre == PID del figlio
        p2 = fork();
        if (!p2)
        {
            printf("Processo figlio2, p: %d, PID: %d, PID padre: %d\n\n", p2, getpid(), getppid());
        }
    }
    else // processo figlio, p è == 0
    {
        printf("Processo figlio1, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
    }
    // il Program Counter punta alla stessa istruzione contenuta sia nel processo padre che nel processo figlio
    return 0;
}