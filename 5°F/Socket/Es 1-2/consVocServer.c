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

void ContaConsVoc(char str[], int *numVoc, int *numCons)
{
    char vocali[] = "aeiouAEIOU";
    for (int i = 0; i < strlen(str); i++)
    {
        if (strchr(vocali, str[i]))
        {
            (*numVoc)++;
        }
        else if (isalpha(str[i]))
        {
            (*numCons)++;
        }
    }
}

void main()
{
    // Variabili
    struct sockaddr_in server, client;
    int socketfd, connessione, length = sizeof(server);

    char str[DIM];
    int numVoc = 0, numCons = 0;
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

    // bind
    bind(socketfd, (struct sockaddr *)&server, sizeof(server));

    // listen
    listen(socketfd, 1);

    while (1)
    {
        printf("\nServer in attesa\n");

        // pulisco il canale
        fflush(stdout);

        // accept
        connessione = accept(socketfd, (struct sockaddr *)&client, &length);

        // lettura
        read(connessione, str, sizeof(str));
        printf("\nStringa ricevuta: %s\n", str);

        ContaConsVoc(str, &numVoc, &numCons);

        write(connessione, &numVoc, sizeof(numVoc));
        write(connessione, &numCons, sizeof(numCons));

        numVoc = 0;
        numCons = 0;

        close(connessione);
    }
}