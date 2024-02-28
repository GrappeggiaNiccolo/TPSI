#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 2048
int main(int argc, char *argv[])
{
    // leggere da file inserito da riga di comando e passare le robe su una fifo

    FILE *origine;
    unsigned char buffer[BUFF_SIZE];
    int fd;

    if (argc != 2)
    {
        printf("numero argomenti sbagliati \n");
        exit(-1);
    }

    // apertura file in lettura
    origine = fopen(argv[1], "r");

    //controllo se file aperto
    if (origine == NULL)
    {
        printf("Il file inserito non esiste \n");
        exit(-1);
    }

    //apertura fifo in scrittura
    fd = open("pipe", O_WRONLY);

    //controllo apertura fifo
    if(fd < 0)
    {
        printf("Errore apertura fifo \n");
        exit(-1);
    }

    //lettura da file e scrittura su fifo
    while (!feof(origine))
    {
        //lettura file
        fread(buffer,1,BUFF_SIZE,origine);

        //scrittura su fifo
        write(fd,buffer,sizeof(buffer));
        
    }

    //chiusura fifo
    close(fd);

    //chiusura file
    fclose(origine);

    //fine programma
    printf("Scrittura finata \n");

    return 0;
}