#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 256
#define SERVERPORT 1025

int main() {
    // Definizione variabili
    struct sockaddr_in server;
    int socketfd;
    char str[DIM];

    // Inizializzazione socket
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // Creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        return -1;
    }

    // Connessione al server
    if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Errore connessione al server");
        close(socketfd);
        return -1;
    }

    // Lettura della stringa dall'input dell'utente
    printf("Inserisci la stringa: ");
    fgets(str, DIM, stdin);
    
    // Rimuovere il newline se presente
    str[strcspn(str, "\n")] = '\0';

    // Invio della stringa al server
    write(socketfd, str, strlen(str) + 1);

    // Ricezione della stringa ordinata dal server
    read(socketfd, str, sizeof(str));
    printf("Stringa ordinata: %s\n", str);

    // Chiusura della socket
    close(socketfd);
    return 0;
}
