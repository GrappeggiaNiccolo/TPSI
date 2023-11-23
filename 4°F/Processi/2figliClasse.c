#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p, i;

int main()
{
    p = getpid();
    printf("Processo padre, p: %d, PID: %d, PID processo generatore(bash ./): %d\n", p, getpid(), getppid());

    for (int i = 0; i < 2; i++)
    {
        
    }
}