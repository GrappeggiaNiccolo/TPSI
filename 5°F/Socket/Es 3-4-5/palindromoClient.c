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

/*Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 1 stringa
e, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il messaggio se
è palindroma oppure non lo è.*/

#define DIM 256
#define SERVERPORT 1025

int main(int argc, char *argv[])
{
    // controllo argomenti
    if (argc != 2)
    {
        printf("\n\nErrore argomenti\n");
        return -1;
    }
    // dichiarazione variabili
    struct sockaddr_in server;
    int socketfd;
    char str[DIM];
    strcpy(str, argv[1]);
    printf("%s", argv[1]);
    // inizializazione socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        return -2;
    }

    // connessione al server
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));

    // invio
    write(socketfd, str, sizeof(str));

    int palindromo = 0;

    // lettura
    read(socketfd, &palindromo, sizeof(palindromo));

    if (palindromo)
    {
        printf("\nLa stringa è palindroma\n");
    }
    else
    {
        printf("\nLa stringa non è palindroma\n");
    }

    // chiusura socket
    close(socketfd);

    return 0;
}