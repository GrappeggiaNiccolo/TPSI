/*Esercizio 9
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input un
vettore di numeri interi, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al
Client il vettore ordinato in modo crescente .*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define SERVERPORT 1025
#define DIM 256

void StampaArray(int arrayAsc[], int size)
{
    printf("\nArray in ordine crescente: ");
    for (int i = 0; i < size; i++)
    {
        if (arrayAsc[i] != 0)
        {
            printf("%d ", arrayAsc[i]);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    int socketfd;
    int array[DIM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, arrayAsc[DIM], size;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // connessione al server
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));

    // scrittura socket
    write(socketfd, array, sizeof(array));

    // lettura socket
    read(socketfd, arrayAsc, sizeof(arrayAsc));

    size = sizeof(arrayAsc) / sizeof(arrayAsc[0]);

    StampaArray(arrayAsc, size);

    close(socketfd);

    return 0;
}