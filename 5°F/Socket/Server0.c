// SERVER
#include <stdio.h>      //std in-out
#include <stdlib.h>     //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h> //funz. accept+bind+listen
#include <sys/types.h>  //funz. accept
#include <netinet/in.h> //definiscono la struttura degli indirizzi
#include <string.h>     //funz. stringhe
#include <errno.h>      //gestioni errori connessione
#include <ctype.h>      //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX

#define DIM 50
#define SERVERPORT 1313

int main()
{
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client ; la struct è presente in <netinet/in.h>,
                                              // serve per memorizzare sia l'indirizzo di rete che della porta
    //  definizione dei dati del socket p.161
    servizio.sin_family = AF_INET;                 // valore fisso ; valorizzazione della struttura
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);  //
    servizio.sin_port = htons(SERVERPORT);         // htons() -> standardizza l'indirizzo IP ; es: da int32 a int16
    int socketfd, soa, fromlen = sizeof(servizio); // socketfd permette di creare la socket, in base al valore che assume determina se il socket è stato creato o meno(0, -1)
    char str[DIM];
    // impostazione del transport endpoint del server p.163-164
    socketfd = socket(AF_INET, SOCK_STREAM, 0); // formato indirizzamento (dominio del socket) , flusso full duplex asimmetrico connection oriented , protocollo (0 è automatico)
    // leghiamo l'indirizzo al transport endpoint p. 164
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio)); // exit code del socket(), puntatore a struttura, dimensione struttura ;
                                                                    // nel client non è fondamentale, ci pensa il SO ; altrimenti serve a stabilire un IP tale, standard
    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd, 10); // puo' attendere fino a 10 client
    // ciclo infinito
    while (1)
    {
        printf("\nServer in ascolto...\n");
        fflush(stdout); // pulisce il canale, alcune stringhe hanno dei caratteri che "sporcano il messaggio"
        // il server accetta la connessione pag. 165
        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, &fromlen);
        // legge dal client
        read(soa, str, sizeof(str));
        printf("Stringa ricevuta: %s\n", str);
        close(soa);
    }
    return 0;
}
