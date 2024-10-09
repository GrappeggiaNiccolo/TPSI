#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Auto {
    char marca[20];
    char ModelloAuto[20];
    int cilindrata;
    int prezzo;
    int AnnoImmatricolazione;
};

// Funzione per trovare la macchina con prezzo minimo e massimo
void PrezzoSort(struct Auto autos[], int len, int *minIndex, int *maxIndex) {
    *minIndex = 0;
    *maxIndex = 0;

    for (int i = 1; i < len; i++) {
        if (autos[i].prezzo < autos[*minIndex].prezzo) {
            *minIndex = i; // aggiorno l'indice del prezzo minore
        }
        if (autos[i].prezzo > autos[*maxIndex].prezzo) {
            *maxIndex = i; // aggiorno l'indice del prezzo maggiore
        }
    }
}

// Funzione per ordinare le auto per anno di immatricolazione
void OrdinaAuto(struct Auto autos[], int len) {
    struct Auto temp;
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (autos[i].AnnoImmatricolazione > autos[j].AnnoImmatricolazione) {
                // Scambio le auto
                temp = autos[i];
                autos[i] = autos[j];
                autos[j] = temp;
            }
        }
    }
}

// Funzione per visualizzare le auto in base al prezzo
void VisualizzaAutoPerPrezzo(struct Auto autos[], int len, int prezzo) {
    printf("Auto con prezzo maggiore o uguale a %d€:\n", prezzo);
    int found = 0;
    for (int i = 0; i < len; i++) {
        if (autos[i].prezzo >= prezzo) {
            printf("- %s %s: %d€\n", autos[i].marca, autos[i].ModelloAuto, autos[i].prezzo);
            found = 1;
        }
    }
    if (!found) {
        printf("Nessuna auto trovata con prezzo maggiore o uguale a %d€.\n", prezzo);
    }
}

int main() {
    // Array di strutture
    struct Auto autos[] = {
        {"Audi", "A4", 2000, 40000, 2009},
        {"BMW", "M3", 3000, 60000, 2023},
        {"Lexus", "LFA", 5000, 500000, 2012},
        {"Renault", "5 turbo", 1400, 15000, 1991},
        {"Fiat", "Panda", 1400, 3000, 1997},
        {"Mercedes", "CLK GTR", 6000, 1000000, 2000},
        {"Porsche", "911", 3000, 100000, 1990}
    };

    int len = sizeof(autos) / sizeof(struct Auto);

    // 1) Prezzo minore e maggiore
    int minIndex, maxIndex;
    PrezzoSort(autos, len, &minIndex, &maxIndex);

    printf("Auto col prezzo minore: %s, prezzo: %d€\n", autos[minIndex].ModelloAuto, autos[minIndex].prezzo);
    printf("Auto col prezzo maggiore: %s, prezzo: %d€\n", autos[maxIndex].ModelloAuto, autos[maxIndex].prezzo);

    // 2) Ordinare la lista delle auto in base all'anno d'immatricolazione
    OrdinaAuto(autos, len);
    printf("\nAuto ordinate per anno di immatricolazione:\n");
    for (int i = 0; i < len; i++) {
        printf("- %s %s, Anno: %d, Prezzo: %d€\n", autos[i].marca, autos[i].ModelloAuto, autos[i].AnnoImmatricolazione, autos[i].prezzo);
    }

    // 3) Visualizzare le auto a partire da un prezzo scelto dall'utente
    int prezzoUtente;
    printf("\nInserire un prezzo per visualizzare le auto: ");
    scanf("%d", &prezzoUtente);
    VisualizzaAutoPerPrezzo(autos, len, prezzoUtente);

    return 0;
}
