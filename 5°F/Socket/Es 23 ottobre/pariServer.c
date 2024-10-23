#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVERPORT 1026
#define DIM 256

// Funzione per sommare i valori di un array
int Somma(int arr[], int size)
{
    int somma = 0;
    for (int i = 0; i < size; i++)
    {
        somma += arr[i];
    }
    return somma;
}

// Funzione per calcolare la media di un array
float Media(int arr[], int size)
{
    if (size == 0) return 0;  // prevenzione di divisione per zero
    int somma = Somma(arr, size);
    return (float)somma / size;
}

// Funzione per estrarre i numeri pari
int Pari(int arr[], int arrPari[], int size)
{
    int cont = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            arrPari[cont] = arr[i];
            cont++;
        }
    }
    return cont;  // ritorna il numero di elementi pari
}

// Funzione per estrarre i numeri dispari
int Dispari(int arr[], int arrDispari[], int size)
{
    int cont = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0)
        {
            arrDispari[cont] = arr[i];
            cont++;
        }
    }
    return cont;  // ritorna il numero di elementi dispari
}

int main()
{
    // dichiarazione variabili
    struct sockaddr_in server, client;
    int arr[DIM], arrPari[DIM], arrDispari[DIM], sommaPari = 0, sommaDispari = 0, socketfd, connessione, len = sizeof(client), size, bytes;
    float mediaPari = 0, mediaDispari = 0;

    // inizializzazione var
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVERPORT);

    // creazione socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // binding del socket
    bind(socketfd, (struct sockaddr *)&server, sizeof(server));
    // inizia l'ascolto
    listen(socketfd, 3);

    while (1)
    {
        printf("\nServer in ascolto...\n");

        // accetta la connessione del client
        connessione = accept(socketfd, (struct sockaddr *)&client, (socklen_t *)&len);

        // legge l'array dal client
        bytes = read(connessione, arr, sizeof(arr));
        size = bytes / sizeof(arr[0]);

        // separa numeri pari e dispari
        int sizePari = Pari(arr, arrPari, size);
        int sizeDispari = Dispari(arr, arrDispari, size);

        // calcola somma e media per numeri pari
        sommaPari = Somma(arrPari, sizePari);
        mediaPari = Media(arrPari, sizePari);

        // calcola somma e media per numeri dispari
        sommaDispari = Somma(arrDispari, sizeDispari);
        mediaDispari = Media(arrDispari, sizeDispari);

        // invia i risultati al client
        write(connessione, &sommaPari, sizeof(sommaPari));
        write(connessione, &mediaPari, sizeof(mediaPari));
        write(connessione, &sommaDispari, sizeof(sommaDispari));
        write(connessione, &mediaDispari, sizeof(mediaDispari));

        // chiude la connessione
        close(connessione);
    }

    // chiusura del socket principale (non raggiunto a causa del ciclo infinito)
    close(socketfd);

    return 0;
}
