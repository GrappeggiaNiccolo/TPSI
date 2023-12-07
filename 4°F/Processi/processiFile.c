#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_NOMI 3
#define MAX_LENGHT_NOME 50

int main() {
    char nomi[MAX_NOMI][MAX_LENGHT_NOME];
    pid_t pid;

    // Input dei nomi da parte dell'utente
    printf("Inserisci 3 nomi:\n");
    for (int i = 0; i < MAX_NOMI; i++) {
        printf("Nome %d: ", i + 1);
        scanf("%s", nomi[i]);
    }

    // Creazione di un processo figlio
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Errore nella fork.\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo figlio

        // Controllo e eliminazione dei doppioni
        for (int i = 0; i < MAX_NOMI - 1; i++) {
            for (int j = i + 1; j < MAX_NOMI; j++) {
                if (strcmp(nomi[i], nomi[j]) == 0) {
                    printf("Il nome %s è duplicato. Verrà rimosso.\n", nomi[j]);
                    nomi[j][0] = '\0';  // Imposta il nome duplicato a una stringa vuota
                }
            }
        }

        // Stampa il risultato
        printf("\nNomi unici:\n");
        for (int i = 0; i < MAX_NOMI; i++) {
            if (nomi[i][0] != '\0') {
                printf("%s\n", nomi[i]);
            }
        }

    } else {
        // Processo padre

        // Attesa del processo figlio
        wait(NULL);

        // Creazione di un file e scrittura dei nomi
        FILE *file = fopen("nomi.txt", "w");
        if (file == NULL) {
            fprintf(stderr, "Impossibile aprire il file.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < MAX_NOMI; i++) {
            fprintf(file, "%s\n", nomi[i]);
        }

        // Chiusura del file
        fclose(file);

        printf("\nFile 'nomi.txt' creato con successo.\n");
    }

    return 0;
}
