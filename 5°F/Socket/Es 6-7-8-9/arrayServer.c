/*Esercizio 6
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input un
vettore di numeri interi, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al
Client la somma e la media del vettore stesso.*/
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

int Somma(int arr[], int size)
{
    int somma = 0;

    for (int i = 0; i < size; i++)
    {
        somma = somma + arr[i];
    }

    return somma;
}
float Media(int arr[], int size)
{
    int somma = Somma(arr, size);

    float media = (float)somma / size;

    return media;
}

void main()
{
    // dichiarazione variabili
    struct sockaddr_in server;
    int arr[DIM], somma = 0, socketfd, len = sizeof(server), connessione, bytes, size;
    float media = 0;

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

        // lettura array dalla socket
        bytes = read(connessione, arr, sizeof(arr));

        // somma e media
        size = bytes / sizeof(arr[0]);
        somma = Somma(arr, size);
        media = Media(arr, size);

        // scrittura nella socket
        write(connessione, &somma, sizeof(somma));
        write(connessione, &media, sizeof(media));

        // chiusura socket
        close(connessione);
    }
}