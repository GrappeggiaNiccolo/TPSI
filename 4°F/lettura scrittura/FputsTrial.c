#include <stdio.h>
#include <stdlib.h>

#define LINEFEED fputc('\n', nomi);

int main(int argc, char *argv[])
{               // in Unix tastiera e monitor sono due file: standard output -> file monitor; standard input -> file tastiera
    FILE *nomi; // puntatore ad oggetto(struttura) di tipo FILE; va usato il puntatore

    char vettNomi[20];
    nomi = fopen("nomi.txt", "a"); // se il file non esiste, lo crea (default: cartella di lavoro; else: specificare)
                                   // w sovrascrive, a aggiunge
    if (nomi == NULL)
    {
        printf("File non aperto, errore");
        fclose(nomi);
        // exit(1);
        return -1;
    }
    
    printf("File aperto\n");

    for (int i = 0; i < 4; i++)
    {
        printf("Inserisci il %d° nome: ", i + 1);
        scanf("%s", vettNomi);
        fputs(vettNomi, nomi);
        //fputs('\n', nomi);
        LINEFEED // --> fputc('\n', nomi);
    }
    fclose(nomi);

    return 0;
}