/*Esercizio 8
crivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input un vettore
di numeri interi, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il
massimo ed il minimo .*/
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

int Max(int arr[], int size)
{
    int max = -__INT32_MAX__;

    for (int i = 0; i < size; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }

    return max;
}
int Min(int arr[], int size)
{
    int min = __INT32_MAX__;

    for (int i = 0; i < size; i++)
    {
        if (min > arr[i])
        {
            min = arr[i];
        }
    }

    return min;
}

void main()
{
    // dichiarazione variabili
    struct sockaddr_in server;
    int arr[DIM], min = 0, max = 0, socketfd, len = sizeof(server), connessione, bytes, size;

    // inizializzazione var
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

    bind(socketfd, (struct sockaddr *)&server, len);

    listen(socketfd, 3);

    while (1)
    {
        printf("\nServer in ascolto\n");

        // pulizia del canale
        fflush(stdout);

        // connessione col client
        connessione = accept(socketfd, (struct sockaddr *)&server, (socklen_t *)&len);

        // lettura array dalla socket, leggo il numero di bytes ricevuti
        bytes = read(connessione, arr, sizeof(arr));

        // minimo e massimo
        size = bytes / sizeof(arr[0]);
        min = Min(arr, size);
        max = Max(arr, size);

        // scrittura nella socket
        write(connessione, &min, sizeof(min));
        write(connessione, &max, sizeof(max));

        // chiusura socket
        close(connessione);
    }
}