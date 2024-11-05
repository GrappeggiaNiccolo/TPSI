#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1025
#define DIM 256

void PariDispari(int arr[], int *pari, int *dispari, int size)
{
    *pari = 0;
    *dispari = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            (*pari)++;
        }
        else
        {
            (*dispari)++;
        }
    }
}

int main()
{
    // variabili
    struct sockaddr_in server, client;
    int socketfd, connessione;
    socklen_t len = sizeof(client);
    int arr[DIM], pari, dispari, size, bytes;

    // inizializzazione varibili server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        return -1;
    }

    // bind
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind");
        close(socketfd);
        return -1;
    }

    // server in ascolto
    listen(socketfd, 2);

    while (1)
    {
        printf("Server in ascolto...\n");

        // pulizia canale
        fflush(stdout);

        // connessione col client accettata
        connessione = accept(socketfd, (struct sockaddr *)&client, &len);
        if (connessione < 0)
        {
            perror("accept");
            continue;
        }

        // lettura dati array e calcolo dimensionw
        bytes = read(connessione, arr, sizeof(arr));
        size = bytes / sizeof(int);

        // num pari e dispari
        PariDispari(arr, &pari, &dispari, size);

        // invio al client
        write(connessione, &pari, sizeof(pari));
        write(connessione, &dispari, sizeof(dispari));

        // chiusura connessione
        close(connessione);
    }

    // chiusura socket
    close(socketfd);
    return 0;
}
