#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMI 3
#define MAX_LENGHT_NOME 50

int main() {
    char nomi[MAX_NOMI][MAX_LENGHT_NOME];
    FILE *file;
    int i, j;

    // Apertura del file in scrittura
    file = fopen("nomi.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file.\n");
        exit(1);
    }

    // Input dei nomi da parte dell'utente
    printf("Inserisci 3 nomi:\n");
    for (i = 0; i < MAX_NOMI; i++) {
        printf("Nome %d: ", i + 1);
        scanf("%s", nomi[i]);
    }

    // Controllo e eliminazione dei doppioni
    for (i = 0; i < MAX_NOMI - 1; i++) {
        for (j = i + 1; j < MAX_NOMI; j++) {
            if (strcmp(nomi[i], nomi[j]) == 0) {
                printf("Il nome %s è duplicato. Verrà rimosso.\n", nomi[j]);
                strcpy(nomi[j], "");  // strcpy(nomi[j], ""); - Imposta il nome duplicato a una stringa vuota
            }
        }
    }

    // Scrittura dei nomi unici nel file
    for (i = 0; i < MAX_NOMI; i++) {
        if (nomi[i][0] != '\0') {
            fprintf(file, "%s\n", nomi[i]);
        }
    }

    // Chiusura del file
    fclose(file);

    // Apertura del file in lettura per stampare il risultato
    file = fopen("nomi.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file.\n");
        exit(1);
    }

    // Stampa il contenuto del file
    printf("\nContenuto del file:\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // Chiusura del file
    fclose(file);

    return 0;
}
