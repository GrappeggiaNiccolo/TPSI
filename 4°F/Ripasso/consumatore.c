#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 2048
int main(int argc, char *argv[])
{
    // legge da fifo e scrive su un file
    int fd;
    int n;
    FILE *destinazione;
    unsigned char buffer[BUFF_SIZE];

    // apertura file
    destinazione = fopen("destinazione.txt", "w");

    // controllo apertura file
    if (destinazione == NULL)
    {
        printf("Errore apertura file \n");
        exit(-1);
    }

    // apertura fifo
    fd = open("pipe", O_RDONLY);

    // lettura da fifo e scrittura su file
    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        fwrite(buffer, 1, sizeof(buffer), destinazione);
    }

    // chiusura fifo
    close(fd);

    // chiusura file
    fclose(destinazione);

    // fine programma
    printf("Fine programma \n");

    return 0;
}