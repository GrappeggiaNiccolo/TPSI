#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 20

// Funzione per controllare se la stringa contiene solo lettere
int ControlloLettere(char stringa[]) {
    for (int i = 0; i < strlen(stringa); i++) {
        if (!isalpha(stringa[i])) {
            return 1; // Restituisce 1 se trova un carattere non lettera
        }
    }
    return 0; // Restituisce 0 se la stringa contiene solo lettere
}

// Funzione per contare le occorrenze di una lettera
int ContaLettera(char stringa[], char c) {
    int cont = 0;
    for (int i = 0; i < strlen(stringa); i++) {
        if (stringa[i] == c) {
            cont++;
        }
    }
    return cont;
}

// Funzione per separare le lettere in posizione pari e dispari
void PariDispari(char stringa[], char pari[], char dispari[]) {
    int contPari = 0;
    int contDispari = 0;
    for (int i = 0; i < strlen(stringa); i++) {
        if (i % 2 == 0) {
            pari[contPari++] = stringa[i];
        } else {
            dispari[contDispari++] = stringa[i];
        }
    }
    pari[contPari] = '\0'; // Terminazione della stringa
    dispari[contDispari] = '\0'; // Terminazione della stringa
}

// Funzione per verificare la presenza di lettere doppie
int Doppie(char stringa[]) {
    for (int i = 0; i < strlen(stringa); i++) {
        for (int j = i + 1; j < strlen(stringa); j++) {
            if (stringa[i] == stringa[j]) {
                return 1; // Restituisce 1 se trova lettere doppie
            }
        }
    }
    return 0; // Restituisce 0 se non ci sono lettere doppie
}

// Funzione per determinare la lunghezza delle stringhe
void Lunghezza(char stringa1[], char stringa2[], char strLunga[], char strCorta[]) {
    if (strlen(stringa1) > strlen(stringa2)) {
        strcpy(strLunga, stringa1);
        strcpy(strCorta, stringa2);
    } else if (strlen(stringa1) < strlen(stringa2)) {
        strcpy(strLunga, stringa2);
        strcpy(strCorta, stringa1);
    } else {
        strcpy(strLunga, stringa1);
        strcpy(strCorta, stringa2);
    }
}

// Funzione per trovare le lettere comuni tra due stringhe
int LettereComuni(char stringa1[], char stringa2[], char lettereComuni[]) {
    int cont = 0;
    for (int i = 0; i < strlen(stringa1); i++) {
        for (int j = 0; j < strlen(stringa2); j++) {
            if (stringa1[i] == stringa2[j]) {
                // Verifica se la lettera non è già stata aggiunta
                int alreadyExists = 0;
                for (int k = 0; k < cont; k++) {
                    if (lettereComuni[k] == stringa1[i]) {
                        alreadyExists = 1;
                        break;
                    }
                }
                if (!alreadyExists) {
                    lettereComuni[cont++] = stringa1[i];
                }
            }
        }
    }
    lettereComuni[cont] = '\0'; // Terminazione della stringa
    return cont; // Restituisce il numero di lettere comuni trovate
}

// Funzione per contare vocali
int ContaVocali(char stringa[]) {
    int cont = 0;
    char vocali[] = "aeiouAEIOU";
    for (int i = 0; i < strlen(stringa); i++) {
        if (strchr(vocali, stringa[i])) {
            cont++;
        }
    }
    return cont;
}

// Funzione per contare consonanti
int ContaConsonanti(char stringa[]) {
    int cont = 0;
    for (int i = 0; i < strlen(stringa); i++) {
        if (isalpha(stringa[i]) && !strchr("aeiouAEIOU", stringa[i])) {
            cont++;
        }
    }
    return cont;
}

int main() {
    char stringa1[LENGTH], stringa2[LENGTH];

    // Inserimento della prima stringa
    printf("Inserire la prima stringa: ");
    scanf("%s", stringa1);
    
    // Inserimento della seconda stringa
    printf("Inserire la seconda stringa: ");
    scanf("%s", stringa2);

    // 1) Controllo se contiene solo lettere
    if (ControlloLettere(stringa1)) {
        printf("\n1) La stringa 1 contiene caratteri non alfabetici\n");
    } else {
        printf("\n1) La stringa 1 contiene solo lettere\n");
    }

    // 2) Conteggio di una lettera specificata
    char c;
    printf("\nInserire una lettera da cercare nella stringa: ");
    scanf(" %c", &c);
    int num = ContaLettera(stringa1, c);
    printf("\n2) La stringa 1 contiene la lettera '%c' %d volte\n\n", c, num);

    // 3) Creazione delle stringhe di lettere pari e dispari
    char pari[LENGTH], dispari[LENGTH];
    PariDispari(stringa1, pari, dispari);
    printf("3) Lettere in posizione pari: %s\n", pari);
    printf("3) Lettere in posizione dispari: %s\n\n", dispari);

    // 4) Verifica di lettere doppie
    if (Doppie(stringa1)) {
        printf("4) La stringa contiene lettere doppie\n\n");
    } else {
        printf("4) La stringa non contiene lettere doppie\n\n");
    }

    // Determinazione della lunghezza delle stringhe
    char strLunga[LENGTH], strCorta[LENGTH];
    Lunghezza(stringa1, stringa2, strLunga, strCorta);
    printf("La stringa più lunga è: %s; la più corta è: %s\n\n", strLunga, strCorta);

    // Lettere contenute in ambedue le stringhe
    char lettereComuni[LENGTH];
    LettereComuni(stringa1, stringa2, lettereComuni);
    printf("3.3) Le lettere in comune sono: %s\n", lettereComuni);

    // 3) Conteggio vocali e consonanti
    int vocaliStringa1 = ContaVocali(stringa1);
    int vocaliStringa2 = ContaVocali(stringa2);
    printf("\n3) La stringa 1 contiene %d vocali e la stringa 2 contiene %d vocali.\n", vocaliStringa1, vocaliStringa2);
    
    if (vocaliStringa1 > vocaliStringa2) {
        printf("La stringa 1 contiene più vocali.\n");
    } else if (vocaliStringa1 < vocaliStringa2) {
        printf("La stringa 2 contiene più vocali.\n");
    } else {
        printf("Entrambe le stringhe contengono lo stesso numero di vocali.\n");
    }

    int consonantiStringa1 = ContaConsonanti(stringa1);
    int consonantiStringa2 = ContaConsonanti(stringa2);
    printf("La stringa 1 contiene %d consonanti e la stringa 2 contiene %d consonanti.\n", consonantiStringa1, consonantiStringa2);
    
    if (consonantiStringa1 > consonantiStringa2) {
        printf("La stringa 1 contiene più consonanti.\n");
    } else if (consonantiStringa1 < consonantiStringa2) {
        printf("La stringa 2 contiene più consonanti.\n");
    } else {
        printf("Entrambe le stringhe contengono lo stesso numero di consonanti.\n");
    }

    return 0;
}