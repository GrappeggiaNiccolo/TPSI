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

int main() {
    // dichiarazionew variabili
    struct sockaddr_in server;
    int socketfd, len = sizeof(server);
    char str1[DIM], str2[DIM], response[DIM];

    // inizializzazione variabili server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(socketfd, (struct sockaddr *)&server, len) < 0) {
        perror("connect");
        return -1;
    }

    // inserimento stringhe
    printf("Inserisci la prima stringa: \n");
    scanf("%s", str1);
    printf("Inserisci la seconda stringa: \n");
    scanf("%s",str2);

    // scrittura al server
    write(socketfd, str1, sizeof(str1));
    write(socketfd, str2, sizeof(str2));
    
    // lettura risultato dal server
    read(socketfd, response, sizeof(response));
    printf("%s\n", response);

    // chiusura socket
    close(socketfd);
    return 0;
}
