#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVERPORT 1026

int main()
{
    // dichiarazione variabili
    struct sockaddr_in server;
    int arr[] = {1, 2, 3, 4, 5}, sommaPari = 0, sommaDispari = 0, socketfd;
    float mediaPari = 0, mediaDispari = 0;

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

    // connessione al server
    if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect");
        close(socketfd);
        exit(-1);
    }

    // invio array al server
    write(socketfd, arr, sizeof(arr));

    // lettura risultato
    read(socketfd, &sommaPari, sizeof(sommaPari));
    read(socketfd, &mediaPari, sizeof(mediaPari));
    read(socketfd, &sommaDispari, sizeof(sommaDispari));
    read(socketfd, &mediaDispari, sizeof(mediaDispari));

    // stampa risultato
    printf("\nSomma pari: %d; Media pari: %.2f\n", sommaPari, mediaPari);
    printf("\nSomma dispari: %d; Media dispari: %.2f\n", sommaDispari, mediaDispari);

    close(socketfd);

    return 0;
}
