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

#define DIM 256
#define SERVERPORT 1025

void main()
{
    // variabili
    struct sockaddr_in server;
    int socketfd; // identificatore socket

    char str1[DIM];
    int numVoc, numCons;
    // inizializzazione socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("socket");
        exit(1);
    }

    // connessione al server
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));
    printf("\nInserisci una stringa: ");
    scanf("%s", str1);

    // invio stringa al server
    write(socketfd, str1, sizeof(str1));

    // lettura dal server
    read(socketfd, &numVoc, sizeof(numVoc));
    printf("\nnumero vocali: %d\n", numVoc);
    read(socketfd, &numCons, sizeof(numCons));
    printf("\nnumero consonanti: %d\n", numCons);

    // chiusura socket
    close(socketfd);
}