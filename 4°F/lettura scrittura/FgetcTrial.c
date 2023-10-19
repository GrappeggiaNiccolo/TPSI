#include <stdio.h>
#include <stdlib.h>

#define LINEFEED fputc('\n', nomi);

int main(int argc, char *argv[])
{               // in Unix tastiera e monitor sono due file: standard output -> file monitor; standard input -> file tastiera
    FILE *nomi; // puntatore ad oggetto(struttura) di tipo FILE; va usato il puntatore

    char vettNomi[20];
    char c;
    nomi = fopen("nomi.txt", "r"); // se il file non esiste, lo crea (default: cartella di lavoro; else: specificare)
                                   // w sovrascrive, a aggiunge, r legge
    if (nomi == NULL)
    {
        printf("File non aperto, errore");
        fclose(nomi);
        // exit(1);
        return -1;
    }
    
    printf("File aperto\n");

    do
    {
        c = fgetc(nomi);
        putchar(c);
    }while(c != EOF); // End Of File --> il punto di domanda

    fclose(nomi);

    return 0;
}