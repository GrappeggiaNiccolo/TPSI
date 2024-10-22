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
    char str[DIM], c;
    int occorrenze;

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

    // Lettura della stringa
    printf("\nInserisci la stringa: ");
    fgets(str, DIM, stdin);  // Usa fgets per gestire correttamente spazi e newline

    // Rimuove il newline alla fine della stringa, se presente
    str[strcspn(str, "\n")] = '\0';

    // Invio stringa
    if (write(socketfd, str, strlen(str) + 1) < 0) {
        perror("Errore invio stringa");
        close(socketfd);
        return -1;
    }

    // Lettura del carattere
    printf("\nInserisci un singolo carattere: ");
    scanf(" %c", &c);  // Nota lo spazio prima di %c per ignorare eventuali caratteri di spaziatura residui

    // Invio carattere
    if (write(socketfd, &c, sizeof(c)) < 0) {
        perror("Errore invio carattere");
        close(socketfd);
        return -1;
    }

    // Ricezione del numero di occorrenze
    if (read(socketfd, &occorrenze, sizeof(occorrenze)) < 0) {
        perror("Errore ricezione occorrenze");
        close(socketfd);
        return -1;
    }

    // Stampa del risultato
    printf("\nOccorrenze del carattere '%c' nella stringa \"%s\": %d\n", c, str, occorrenze);

    // Chiusura socket
    close(socketfd);

    return 0;
}
