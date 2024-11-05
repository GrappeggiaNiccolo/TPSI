#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

/*Esercizio 10
Scrivere il codice in C, di un applicazione Socket CLIENT-SERVER in cui il server riceve in input 2 stringhe
e, dopo aver effettuato gli eventuali ed opportuni controlli (se necessari), rispedisce al Client il messaggio di
quale delle due stringhe è + lunga o più corta o se sono uguali.*/

#define SERVERPORT 1025
#define DIM 256

int main()
{
    // dichiarazione variabili
    struct sockaddr_in server, client;
    int socketfd, connessione, len = sizeof(client);
    char str1[DIM], str2[DIM], response[DIM];

    // inizializzazione variabili server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // bind
    bind(socketfd, (struct sockaddr *)&server, len);

    // ascolto
    listen(socketfd, 2);

    while (1)
    {
        printf("Server in ascolto...");
        fflush(stdout);

        // connessione col client
        connessione = accept(socketfd, (struct sockaddr *)&client, (socklen_t *)&len);

        // lettura stringhe dal client 
        read(connessione, str1, sizeof(str1));
        read(connessione, str2, sizeof(str2));

        if (strlen(str1) > strlen(str2))
        {
            strcpy(response, "La prima stringa è più lunga.");
        }
        else if (strlen(str1) < strlen(str2))
        {
            strcpy(response, "La seconda stringa è più lunga.");
        }
        else
        {
            strcpy(response, "Le due stringhe sono uguali.");
        }

        // scrittura al client
        write(connessione, response, sizeof(response));

        // chiusura connessione
        close(connessione);
    }

    return 0;
}
