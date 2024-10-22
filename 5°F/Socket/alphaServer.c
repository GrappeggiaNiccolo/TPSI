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

// Funzione per rimuovere i caratteri speciali da una stringa
void rimuoviCaratteriSpeciali(const char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (isalpha(input[i])) { // Controlla se il carattere è alfabetico
            output[j++] = input[i];
        }
    }
    output[j] = '\0'; // Aggiungi il terminatore
}

// Funzione per ordinare la stringa
void ordinaStringa(char *str) {
    for (int i = 0; str[i]; i++) {
        for (int j = i + 1; str[j]; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    // Definizione variabili
    struct sockaddr_in server, client;
    int socketfd, connessione, length = sizeof(client);
    char str[DIM], strPulita[DIM];

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

    // Bind della socket
    if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        return -1;
    }

    // Inizio ad ascoltare le connessioni
    listen(socketfd, 1);
    printf("Server in attesa di connessioni...\n");

    while (1) {
        // Accettazione della connessione del client
        connessione = accept(socketfd, (struct sockaddr *)&client, &length);
        if (connessione < 0) {
            perror("Errore nell'accettazione della connessione");
            continue;
        }

        // Lettura della stringa dal client
        read(connessione, str, sizeof(str));
        printf("Ricevuta stringa: %s\n", str);

        // Rimuovere i caratteri speciali
        rimuoviCaratteriSpeciali(str, strPulita);
        printf("Stringa dopo rimozione caratteri speciali: %s\n", strPulita);

        // Ordinamento della stringa
        ordinaStringa(strPulita);

        // Scrittura della stringa ordinata al client
        write(connessione, strPulita, strlen(strPulita) + 1);

        // Chiusura della connessione
        close(connessione);
    }

    // Chiusura della socket
    close(socketfd);
    return 0;
}
