#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h> // FIFO
int main()
{
    // Dichiarazione var
    int fd; // Handle
    // int x = 90 --> errore, va inizializzata dopo l'apertura della fifo

    //  Creazione FIFO
    if (mkfifo("Fifo1", 0777) == -1) // 0777 da tutti i permessi
    {
        printf("Errore creazione fifo\n");
        return -1;
    }

    // Apertura Fifo in write
    fd = open("Fifo1", O_WRONLY); // se == -1, errore
    printf("Aperta FiFo\n");

    // Inizializzazione
    int x = 90;

    if (write(fd, &x, sizeof(x)))
    {
        printf("Errore scrittura fifo\n");
        return -1;
    }

    printf("Scrittura nella fifo...\n");

    close(fd);
    return 0;
}