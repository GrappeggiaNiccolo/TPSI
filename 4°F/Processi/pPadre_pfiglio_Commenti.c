#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int p; // variabile intera per gestire processo padre e figlio
       // PID del padre == PID figlio, mentre PID figlio == 0

int main(int argc, char *argv[])
{               // ciò che fa il processo padre e quello figlio si distingue dal
    p = fork(); // padre genera un processo figlio --> genera un processo (il processo originale è Main)
                // numero che ritorna la fork per distinguere

    if (p != 0) // processo padre
    {
        printf("Processo padre, p: %d, PID: %d, PID processo generatore(bash ./): %d\n", p, getpid(), getppid());    // p del padre == PID del figlio
    }
    else // processo figlio, p è == 0
    {
        printf("Processo figlio, p: %d, PID: %d, PID padre: %d\n\n", p, getpid(), getppid());
    }
    // il Program Counter punta alla stessa istruzione contenuta sia nel processo padre che nel processo figlio
    return 0;
}

// 3) se viene dichiarata dentro il main per essere usata dalle funzioni dovrà essere passata ogni volta
// 4) le istruzioni eseguite prima della fork vengonoi eseguite dal processo padre
// 5) il processo padre del processo padre è il terminale, perché è colui che manda in esecuzione il programma