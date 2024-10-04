/*L'obiettivo è quello di creare una rappresentazione per i e le a cui appartengono. 
Ogni libro avrà diverse informazioni e sarà assegnato a una categoria specifica.

Implementa un programma in linguaggio C che gestisce i libri di una libreria.
Ogni libro è identificato da titolo, autore, anno di pubblicazione e prezzo. 
I libri sono organizzati per categoria (ad esempio, narrativa, saggistica, scienze, arte), e ogni categoria può avere più libri.
Immaginate di dover gestire questi raccolta di libri, suddivisi per categorie, 
e di dover trovare un modo per tenere traccia delle informazioni di ciascun libro. 
Ogni libro dovrà avere un titolo, che lo identificherà, un autore, che ci dirà chi ha scritto il libro, l'anno di pubblicazione, 
che ci permetterà di sapere quando è stato pubblicato, e infine un prezzo, per indicare quanto costa.
Dovrete anche pensare a come suddividere questi libri in categorie. 
Ogni categoria avrà un nome, che indicherà di che tipo di libri stiamo parlando, come "Narrativa" o "Scienze", 
e conterrà una lista di libri che appartengono a quella specifica categoria.
Il vostro compito sarà trovare il modo migliore per organizzare e gestire tutte queste informazioni. 
Inoltre, dovrete scrivere delle funzioni che vi permettano di stampare tutti i libri che appartengono a una determinata categoria, 
cercare un libro specifico in base al titolo e trovare tutti i libri che rientrano in una certa categoria.
Sarà vostro compito decidere come rappresentare questi dati e implementare le funzioni necessarie per far funzionare il programma.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LIBRI 100

// Definizione della struct Libro
struct Libro {
    char titolo[20];
    char autore[20];
    int anno;
    float prezzo;
    char categoria[20];  // Campo che verrà lasciato vuoto
};

// Funzione per leggere il CSV e salvare i dati nella struct
int EsportaCSV(const char *filename, struct Libro libri[], int max_libri) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return -1;
    }

    char linea[MAX_LINE_LENGTH];
    int count = 0;

    // Salta l'intestazione del CSV
    if (fgets(linea, sizeof(linea), file) == NULL) {
        fclose(file);
        return -1;  // Se il file è vuoto o c'è stato un errore
    }

    // Leggi le righe successive e salva i dati nella struct
    while (fgets(linea, sizeof(linea), file) != NULL && count < max_libri) {
        struct Libro libro;

        // Dividi la linea usando la virgola come delimitatore
        char *token = strtok(linea, ",");
        if (token != NULL) strncpy(libro.titolo, token, sizeof(libro.titolo));

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(libro.autore, token, sizeof(libro.autore));

        token = strtok(NULL, ",");
        if (token != NULL) libro.anno = atoi(token);  // Converti l'anno in intero

        token = strtok(NULL, ",");
        if (token != NULL) libro.prezzo = atof(token);  // Converti il prezzo in float

        // Inizializza il campo "categoria" come stringa vuota
        strcpy(libro.categoria, "");

        // Aggiungi il libro all'array
        libri[count++] = libro;
    }

    fclose(file);
    return count;  // Ritorna il numero di libri letti
}

// Funzione per stampare i libri
void stampa_libri(struct Libro libri[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Titolo: %s, Autore: %s, Anno: %d, Prezzo: %.2f, Categoria: %s\n", 
               libri[i].titolo, libri[i].autore, libri[i].anno, libri[i].prezzo, libri[i].categoria);
    }
}

int main() {
    struct Libro libri[MAX_LIBRI];  // Array di struct per memorizzare i libri
    int count = EsportaCSV("libri.csv", libri, MAX_LIBRI);  // Leggi i dati dal CSV

    if (count > 0) {
        printf("Sono stati letti %d libri dal file CSV:\n", count);
        stampa_libri(libri, count);  // Stampa i libri letti

        // Esempio di inserimento manuale della categoria
        for (int i = 0; i < count; i++) {
            printf("Inserisci la categoria per il libro '%s': ", libri[i].titolo);
            fgets(libri[i].categoria, sizeof(libri[i].categoria), stdin);
            // Rimuove il carattere di newline che fgets aggiunge
            libri[i].categoria[strcspn(libri[i].categoria, "\n")] = 0;
        }

        // Stampa i libri con le categorie inserite
        printf("\nLibri aggiornati con le categorie:\n");
        stampa_libri(libri, count);
    } else {
        printf("Errore durante la lettura del file CSV.\n");
    }

    return 0;
}

