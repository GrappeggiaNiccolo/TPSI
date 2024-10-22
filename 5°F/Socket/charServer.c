#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define DIM 256
#define SERVERPORT 1025

// Funzione per contare le occorrenze di un carattere in una stringa
int ContaOccorrenze(char str[], char c) {
    int cont = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (tolower(str[i]) == tolower(c)) {  // Confronto case-insensitive
            cont++;
        }
    }
    return cont;
}

int main() {
    // Definizione variabili
    struct sockaddr_in server, client;
    int socketfd, connessione;
    socklen_t client_len = sizeof(client);
    char str[DIM], c;
    int occorrenze;

    // Inizializzazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Errore creazione socket");
        return -1;
    }

    // Configurazione dell'indirizzo del server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);  // Accetta connessioni da qualsiasi indirizzo
    server.sin_port = htons(SERVERPORT);

    // Binding: associazione della socket all'indirizzo IP e alla porta
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Errore binding");
        close(socketfd);
        return -1;
    }

    // Messa in ascolto del server per accettare connessioni
    if (listen(socketfd, 1) < 0) {
        perror("Errore listen");
        close(socketfd);
        return -1;
    }

    // Loop principale del server per accettare connessioni
    while (1) {
        printf("\nServer in attesa di connessioni...\n");

        // Accetta connessione da un client
        connessione = accept(socketfd, (struct sockaddr *)&client, &client_len);
        if (connessione < 0) {
            perror("Errore accettazione connessione");
            continue;
        }

        // Lettura della stringa e del carattere inviati dal client
        if (read(connessione, str, sizeof(str)) <= 0) {
            perror("Errore lettura stringa");
            close(connessione);
            continue;
        }

        if (read(connessione, &c, sizeof(c)) <= 0) {
            perror("Errore lettura carattere");
            close(connessione);
            continue;
        }

        // Conta le occorrenze del carattere nella stringa
        occorrenze = ContaOccorrenze(str, c);

        // Stampa il risultato lato server
        printf("\nOccorrenze del carattere '%c' nella stringa \"%s\": %d\n", c, str, occorrenze);

        // Invia il numero di occorrenze al client
        if (write(connessione, &occorrenze, sizeof(occorrenze)) <= 0) {
            perror("Errore invio occorrenze");
        }

        // Chiudi la connessione con il client
        close(connessione);
    }

    // Chiudi il socket del server
    close(socketfd);

    return 0;
}
