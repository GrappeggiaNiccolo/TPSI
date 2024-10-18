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

int Palindromo(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] != str[len - i - 1])  // Confrontiamo caratteri speculari
        {
            return 0;  // Se uno non combacia, la stringa non è un palindromo
        }
    }
    return 1;  // Se tutti i caratteri combaciano, è un palindromo
}

int main(int argc, char *argv[])
{
    // dichiarazione variabili
    struct sockaddr_in server, client;
    int socketfd, connessione, length = sizeof(server);
    char str[DIM];
    int palindromo = 0;

    // inizializzazione
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
    bind(socketfd, (struct sockaddr *)&server, sizeof(server));

    // listen
    listen(socketfd, 1);

    while (1)
    {
        printf("\nServer in attesa");

        // pulisco il canale
        fflush(stdout);

        // connessione del client
        connessione = accept(socketfd, (struct sockaddr *)&server, &length);

        // lettura dal client
        read(connessione, str, sizeof(str));
        printf("\nStringa: %s", str);

        // Contollo se è palindroma
        palindromo = Palindromo(str);

        write(connessione, &palindromo, sizeof(palindromo));

        close(connessione);
    }

    return 0;
}