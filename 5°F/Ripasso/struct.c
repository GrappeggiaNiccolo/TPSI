#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esercizio 3 - Strutture
Scrivere un programma in C che dopo aver dichiarato una struttura denominata Auto con i seguenti
campi: ModelloAuto, marca, cilindrata, prezzo, anno_immatricolazione, determinare:
1) Il prezzo + alto e quello + basso visualizzando anche il modello dell'auto;
2) Ordinare la lista delle auto in base all'anno d'immatricolazione;
3) Visualizzare il nome delle auto a partire da un prezzo scelto dall'utente.*/

struct Auto
{
    char marca[20];
    char ModelloAuto[20];
    int cilindrata;
    int prezzo;
    int AnnoImmatricolazione;
};

// Funzione per trovare la macchina con prezzo minimo e massimo
void PrezzoSort(struct Auto autos[], int len, int *minIndex, int *maxIndex)
{
    *minIndex = 0;
    *maxIndex = 0;

    for (int i = 1; i < len; i++) // parte dal secondo elemento
    {
        if (autos[i].prezzo < autos[*minIndex].prezzo)
        {
            *minIndex = i; // se il prezzo è minore aggiorno l'indice
        }
        if (autos[i].prezzo > autos[*maxIndex].prezzo)
        {
            *maxIndex = i; // se il prezzo è minore aggiorno l'indice
        }
    }
}

int main(int argc, char *argv[])
{
    // Array di strutture
    struct Auto autos[] = {
        {"Audi", "A4", 2000, 40000, 2009},
        {"BMW", "M3", 3000, 60000, 2023},
        {"Lexus", "LFA", 5000, 500000, 2012},
        {"Renault", "5 turbo", 1400, 15000, 1991},
        {"Fiat", "Panda", 1400, 3000, 1997},
        {"Mercedes", "CLK GTR", 6000, 1000000, 2000},
        {"Porsche", "911", 3000, 100000, 1990}};

    int len = sizeof(autos) / sizeof(struct Auto);

    // 1) Prezzo minore e maggiore
    int minIndex, maxIndex;
    PrezzoSort(autos, len, &minIndex, &maxIndex);

    printf("Auto col prezzo minore: %s, prezzo: %d€\n", autos[minIndex].ModelloAuto, autos[minIndex].prezzo);
    printf("Auto col prezzo maggiore: %s, prezzo: %d€\n", autos[maxIndex].ModelloAuto, autos[maxIndex].prezzo);

    // 2) Ordinare la lista delle auto in base all'anno d'immatricolazione

    return 0;
}
