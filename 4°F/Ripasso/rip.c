#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 2

typedef struct {
    int matricola;
    char nome[30];
    double media;
} Studente;

int main(int argc, char *argv[]) {
    Studente sArray[N];
    int fd[2], p;

    if (pipe(fd) == -1) {
        perror("Errore pipe");
        exit(EXIT_FAILURE);
    }

    if ((p = fork()) == -1) {
        perror("Errore fork");
        exit(EXIT_FAILURE);
    }

    if (!p) { // figlio

        // chiusura scrittura pipe
        close(fd[1]);

        // apertura file
        FILE *file = fopen("destinazione.txt", "w");
        if (file == NULL) {
            perror("Errore apertura file");
            exit(EXIT_FAILURE);
        }

        // lettura pipe
        read(fd[0], &sArray, sizeof(Studente) * N);
        
        // scrittura nel file
        fwrite(sArray, sizeof(Studente), N, file);

        // chiusura file
        fclose(file);

        // chiusura pipe
        close(fd[0]);

        exit(EXIT_SUCCESS);
    }

    // padre

    close(fd[0]); // chiusura lettura pipe

    for (int i = 0; i < N; i++) {
        printf("Inserisci la matricola di un nuovo studente: \n");
        scanf("%d", &sArray[i].matricola);
        printf("Inserisci il nome del nuovo studente: \n");
        scanf("%s", sArray[i].nome);
        printf("Inserisci la media del nuovo studente: \n");
        scanf("%lf", &sArray[i].media);
    }

    // scrittura in pipe
    write(fd[1], &sArray, sizeof(sArray));

    // chiusura scrittura pipe
    close(fd[1]);

    return 0;
}
