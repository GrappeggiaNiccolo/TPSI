/*Creare un programma in C che genera una sequenza di 10.000
numeri casuali e li memorizza in un array; i numeri generati devono appartenere
all’intervallo 1-500.
Nel programma il processo padre genera due figli e la suddivisione dei compiti deve essere come segue:
-         Il padre genera i 10.000 numeri casuali.
-         Il padre salva tutti i numeri casuali in un file con il formato indice_array : valore
-         Il padre ricerca all’interno dei primi 2000 numeri dell’array un numero X inserito dall’utente a linea di comando e stampa a video la coppia indice_array : valore per tutte le coppie trovate; la stampa di ogni coppia deve essere preceduta dal pid del processo.
-         I due figli svolgono lo stesso compito del punto precedente dividendosi il lavoro a metà (4000 ricerche ciascuno).*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int length = 10000;
    int numeri[length];
    int randomNumber;
    int h = 0;
    FILE *file;

    // Seed the random number generator with the current time
    srand(time(NULL));

    file = fopen("numeri.txt", "w");

    // ERR check
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file for writing\n");
        return -1;
    }
    // RNG
    for (int i = 0; i < 5; i++)
    {
        h++;
        randomNumber = (rand() % 500) + 1;
        fprintf(file, "%d : %d\n", h, randomNumber);
    }
    fclose(file);

    fopen("numeri.txt", "r");
    // ERR check
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file for writing\n");
        return -1;
    }
    // Lettura
    while (fscanf(file, "%d", &randomNumber) == 1)
    {
        printf("%c\n", (char)randomNumber);
    }
    int x;

    // sprintf();
    // Scrittura a video-
    char buffer[8], ch, ch2;
    int j = 0, k = 0, cont = 0;
    while (cont < 5) // (ch = fgetc(file)) != EOF
    {
        // Initialize to '\0' using memset
        memset(buffer, '\0', sizeof(buffer));
        // Porta il file all'indice voluto
        fseek(file, k, SEEK_SET);
        while ((ch2 = fgetc(file)) != '\n')
        {
            buffer[j] = ch2;
            j++;
        }
        k += j; // per partire a leggere il file da una nuova riga gli aggiungo i caratteri letti, poi incremento di 1 per compensare lo '\n' che non viene letto
        k++;
        j = 0;
        cont++;
        printf("%s\n", buffer);
    }

    fclose(file);
    return 0;
}