#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVERPORT 1025
#define DIM 256

int main() {
    struct sockaddr_in server;
    int socketfd;
    int arr[DIM] = {1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7, 7}; 
    int pari, dispari;

    // inizializzazione variabili server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socvket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("socket");
        return -1;
    }

    // connesione al server
    if (connect(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(socketfd);
        return -1;
    }

    // Invio array al server
    write(socketfd, arr, sizeof(arr));

    // lettura risultati dal serrver
    read(socketfd, &pari, sizeof(pari));
    read(socketfd, &dispari, sizeof(dispari));

    // stampa riusultati
    printf("\nNumeri pari: %d ; Numeri dispari: %d\n", pari, dispari);

    // chiusura socket
    close(socketfd);
    return 0;
}
