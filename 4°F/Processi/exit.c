// exit x; x = variabile status 0-255, vengono usati solo i due byte meno significativi, il secondo byte indica che è terminata la wait ?con successo?
// Pipe = canale di comunicazione tra processi
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include the header for wait()
#include <sys/types.h> // Add this line

int p;  // PID del padre == PID figlio, mentre PID figlio == 0

int status;

int main(int argc, char *argv[])
{               // ciò che fa il processo padre e quello figlio si distingue dal
    p = fork(); // padre genera un processo figlio --> genera un processo (il processo originale è Main)
                // numero che ritorna la fork per distinguere

    if (p != 0) // processo padre
    {
        printf("Processo padre, p: %d, PID: %d, PID processo generatore(bash ./): %d\n", p, getpid(), getppid());    // p del padre == PID del figlio
        printf("Wait (PID figlio): %d\n", wait(&status)); // aspetta che il figlio finisca/muoia 
        printf("il codice di terminazione figlio: WEXITSTATUS(status) = %d\n", WEXITSTATUS(status)); //This macro helps in retrieving the least significant 8 bits of the status value, which represent the exit status of the child process.
        printf("il codice di terminazione figlio: WEXITSTATUS(status) = %d\n\n", status); // 25 --> 6400 ; (000)1 1001 | 0000 0000
    }
    else // processo figlio, p è == 0
    {
        printf("Processo figlio, p: %d, PID: %d, PID padre: %d\n", p, getpid(), getppid());
        exit(25);
    }
    // il Program Counter punta alla stessa istruzione contenuta sia nel processo padre che nel processo figlio
    return 0;
}