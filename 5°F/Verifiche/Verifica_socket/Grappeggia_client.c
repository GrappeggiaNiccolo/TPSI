#include <stdio.h> // libreria per funzioni di base (printf(), scanf(), ecc..)
#include <stdlib.h>
#include <sys/socket.h> // libreria per l'utilizzo delle socket
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h> // libreria per l'utilizzo di funzioni che effettuano controlli sui caratteri (isalpha(), isdigit(), ecc...)
#include <unistd.h>

/*Scrivere il codice di un'applicazione socket client-server in linguaggio C.
L'applicazione deve consentire al client di inviare al server una stringa di testo.
Il server dovrà analizzare la stringa ricevuta dal client e restituire al client due stringhe separate.
La prima stringa dovrà contenere tutti i caratteri numerici dalla stringa di input,
mentre la seconda stringa conterrà tutti gli altri caratteri escluse le lettere maiuscole e minuscole.*/

// definizione di costanti, la porta del server e la dimensione massima delle stringhe
#define SERVERPORT 1025
#define DIM 256

int main(int argc, char *argv[])
{
    // dichiarazione variabili
    struct sockaddr_in server;
    int socketfd;
    socklen_t len = sizeof(server);

    char str[DIM], strNum[DIM], strSp[DIM];

    // strcpy(str, "ciao1234@ciao"); -- prova

    // inserimento stringa da linea di comando
    // controllo gli argomenti inseriti e la dimensione della stringa inserita
    if (argc != 2)
    {
        perror("argomenti");
        return -1;
    }
    if (strlen(argv[1]) > DIM)
    {
        perror("size");
        return -1;
    }
    strcpy(str, argv[1]);

    // inizializzazione variabili server
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

    // connessione al server
    if (connect(socketfd, (struct sockaddr *)&server, len) < 0)
    {
        perror("connect");
        return -1;
    }

    // invio stringa al server
    write(socketfd, str, sizeof(str));

    // lettura delle stringhe elaborate dal server
    read(socketfd, strNum, sizeof(strNum));
    read(socketfd, strSp, sizeof(strSp));

    // stampa a video dei risultati
    printf("Stringa iniziale: %s\nStringa numerica: %s\nStringa caratteri speciali: %s\n", str, strNum, strSp);

    // chiusura della connessione
    close(socketfd);

    return 0;
}