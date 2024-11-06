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

int main() {
    // dichiarazione variabili
    struct sockaddr_in server;
    int arr[] = {1,2,3,4,5}, somma = 0, socketfd;
    float media = 0;

    // inizializzazione var
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if(socketfd == -1) {
        perror("socket");
        exit(-1);
    }

    // connessione al server
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));

    // scrittura sulla socket
    write(socketfd, arr, sizeof(arr));

    // lettura risultato
    read(socketfd, &somma, sizeof(somma));
    read(socketfd, &media, sizeof(media));

    // stampa risultato
    printf("\nSomma: %d; Media: %.2f\n", somma, media);

    close(socketfd);

    return 0;
}