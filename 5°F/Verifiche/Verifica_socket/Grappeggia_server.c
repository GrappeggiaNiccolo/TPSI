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

// funzione che mi permette di estrarre due stringhe da una iniziale:
// la prima conterrà i caratteri numerici, la seconda i caratteri speciali (cioè i caratteri che non sono alfanumerici)
void StringheNumSp(char str[], char strNum[], char strSp[])
{
    int contNum = 0; // contatore ausiliario per la stringa strNum
    int contSp = 0; // contatore ausiliario per la stringa strSp

    // ciclo che itera per tutti gli elementi della stringa
    for (int i = 0; i < DIM; i++)
    {
        if (isdigit(str[i])) // verifica che il carattere sia una cifra tra 0 - 9
        {
            strNum[contNum] = str[i];
            contNum++;
        }
        else if (!isalnum(str[i])) // è equivalente al controllo (isalpha(c) || isdigit(c)), verifica quindi che non ci siano caratteri alfanumerici
        {
            strSp[contSp] = str[i];
            contSp++;
        }
    }
}

int main()
{
    // dichiarazione variabili
    struct sockaddr_in server, client;
    int socketfd, soa;
    socklen_t len = sizeof(server);

    char str[DIM], strNum[DIM], strSp[DIM];

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

    // collego il processo alla socket
    if (bind(socketfd, (struct sockaddr *)&server, len) < 0)
    {
        perror("bind");
        return -1;
    }

    // metto il server in attesa di una connessione -> primitiva listen
    listen(socketfd, 2);

    // uso un ciclo infinito per far restare il server in attesa di più client
    while (1)
    {
        printf("Server in ascolto...\n");

        // pulisco il canale
        fflush(stdout);

        // accetto la connessione del client
        soa = accept(socketfd, (struct sockaddr *)&client, &len);

        if (soa < 0)
        {
            perror("accept");
            return -1;
        }

        // leggo la stringa inviata dal client
        read(soa, str, sizeof(str));

        // elaboro la stringa
        StringheNumSp(str, strNum, strSp);

        // invio le stringhe al client
        write(soa, strNum, sizeof(strNum));
        write(soa, strSp, sizeof(strSp));

        // chiudo la connessione col client
        close(soa);
    }

    return 0;
}