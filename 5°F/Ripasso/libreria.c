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
#define MAX_TITOLO 100
#define MAX_AUTORE 50
#define MAX_CATEGORIA 30
#define FILE_BINARIO "libreria.bin" // Nome del file binario per la persistenza

// Definizione della struct Libro
struct Libro
{
    char titolo[MAX_TITOLO];
    char autore[MAX_AUTORE];
    int anno;
    float prezzo;
    char categoria[MAX_CATEGORIA]; // Campo per la categoria
};

// Funzione per leggere il CSV e salvare i dati nella struct
int leggi_csv(const char *filename, struct Libro libri[], int max_libri)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Errore nell'apertura del file");
        return -1;
    }

    char linea[MAX_LINE_LENGTH];
    int count = 0;

    // Salta l'intestazione del CSV
    if (fgets(linea, sizeof(linea), file) == NULL)
    {
        fclose(file);
        return -1; // Se il file è vuoto o c'è stato un errore
    }

    // Leggi le righe successive e salva i dati nella struct
    while (fgets(linea, sizeof(linea), file) != NULL && count < max_libri)
    {
        struct Libro libro;

        // Dividi la linea usando la virgola come delimitatore
        char *token = strtok(linea, ",");
        if (token != NULL)
            strncpy(libro.titolo, token, sizeof(libro.titolo));

        token = strtok(NULL, ",");
        if (token != NULL)
            strncpy(libro.autore, token, sizeof(libro.autore));

        token = strtok(NULL, ",");
        if (token != NULL)
            libro.anno = atoi(token); // Converti l'anno in intero

        token = strtok(NULL, ",");
        if (token != NULL)
            libro.prezzo = atof(token); // Converti il prezzo in float

        // Inizializza il campo "categoria" come stringa vuota
        strcpy(libro.categoria, "");

        // Aggiungi il libro all'array
        libri[count++] = libro;
    }

    fclose(file);
    return count; // Ritorna il numero di libri letti
}

// Funzione per salvare i dati dei libri in un file binario
void salva_file_binario(const char *filename, struct Libro libri[], int count)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Errore nell'apertura del file binario per la scrittura");
        return;
    }

    fwrite(libri, sizeof(struct Libro), count, file); // Scrive l'array di struct nel file binario
    fclose(file);
}

// Funzione per caricare i dati dal file binario
int carica_file_binario(const char *filename, struct Libro libri[], int max_libri)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        return -1; // Se il file non esiste, ritorna -1
    }

    int count = fread(libri, sizeof(struct Libro), max_libri, file); // Legge l'array di struct dal file binario
    fclose(file);
    return count;
}

// Funzione per stampare i libri in formato tabellare, incluso il campo "categoria"
void Visualizza(struct Libro libri[], int count, const char *categoria)
{
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("| %-31s | %-30s | %-4s | %-6s | %-15s |\n", "Titolo", "Autore", "Anno", "Prezzo", "Categoria");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        // Se la categoria fornita non è nulla e non corrisponde, salta il libro
        if (categoria != NULL && strlen(categoria) > 0 && strcmp(libri[i].categoria, categoria) != 0)
        {
            continue;
        }

        // Stampa il libro in formato tabellare
        printf("| %-31s | %-30s | %-4d | %-6.2f | %-15s |\n",
               libri[i].titolo, libri[i].autore, libri[i].anno, libri[i].prezzo, libri[i].categoria);
    }

    printf("------------------------------------------------------------------------------------------------------\n");
}

// Funzione per inserire manualmente le categorie dei libri
void inserisci_categorie(struct Libro libri[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Inserisci la categoria per il libro '%s': ", libri[i].titolo);
        fgets(libri[i].categoria, sizeof(libri[i].categoria), stdin);
        // Rimuove il carattere di newline che fgets aggiunge
        libri[i].categoria[strcspn(libri[i].categoria, "\n")] = 0;
    }

    // Salva l'array aggiornato nel file binario
    salva_file_binario(FILE_BINARIO, libri, count);
}

// Funzione per visualizzare i libri appartenenti a una determinata categoria
void visualizza_libri_per_categoria(struct Libro libri[], int count)
{
    char categoria[MAX_CATEGORIA];

    // Chiede all'utente di inserire la categoria desiderata
    printf("Inserisci la categoria da visualizzare: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = 0; // Rimuove il newline

    printf("\nLibri appartenenti alla categoria '%s':\n", categoria);
    Visualizza(libri, count, categoria); // Stampa solo i libri della categoria specificata
}

// Funzione per cercare un libro specifico in base al titolo
void cerca_libro_per_titolo(struct Libro libri[], int count)
{
    char titolo[MAX_TITOLO];

    // Chiede all'utente di inserire il titolo del libro da cercare
    printf("Inserisci il titolo del libro da cercare: ");
    fgets(titolo, sizeof(titolo), stdin);
    titolo[strcspn(titolo, "\n")] = 0; // Rimuove il newline

    // Cerca il libro corrispondente al titolo inserito
    int trovato = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(libri[i].titolo, titolo) == 0) // Confronto case-insensitive
        {
            // Se il libro è trovato, stampa i dettagli
            printf("\nLibro trovato:\n");
            printf("Titolo: %s\n", libri[i].titolo);
            printf("Autore: %s\n", libri[i].autore);
            printf("Anno: %d\n", libri[i].anno);
            printf("Prezzo: %.2f\n", libri[i].prezzo);
            printf("Categoria: %s\n", libri[i].categoria);
            trovato = 1;
            break;
        }
    }

    if (!trovato)
    {
        printf("Nessun libro trovato con il titolo '%s'.\n", titolo);
    }
}

// Menu con le opzioni per l'utente
void menu(struct Libro libri[], int count)
{
    int scelta;

    do
    {
        // Stampa il menu
        printf("\n--- Menu ---\n");
        printf("1. Inserisci categorie manualmente\n");
        printf("2. Visualizza tutti i libri\n");
        printf("3. Visualizza libri per categoria\n");
        printf("4. Cerca un libro per titolo\n");
        printf("0. Esci\n");
        printf("Scegli un'opzione: ");
        scanf("%d", &scelta);
        getchar(); // Per consumare il newline rimasto nel buffer di input

        switch (scelta)
        {
        case 1:
            inserisci_categorie(libri, count); // Inserisci le categorie e salva nel file binario
            break;
        case 2:
            Visualizza(libri, count, NULL); // Visualizza tutti i libri senza filtro
            break;
        case 3:
            visualizza_libri_per_categoria(libri, count); // Visualizza i libri di una specifica categoria
            break;
        case 4:
            cerca_libro_per_titolo(libri, count); // Cerca un libro per titolo
            break;
        case 0:
            printf("Uscita dal programma.\n\n");
            break;
        default:
            printf("Opzione non valida, riprova.\n");
        }
    } while (scelta != 0);
}

int main()
{
    struct Libro libri[MAX_LIBRI]; // Array di struct per memorizzare i libri
    int count;

    // Prova a caricare i dati dal file binario
    count = carica_file_binario(FILE_BINARIO, libri, MAX_LIBRI);

    if (count > 0)
    {
        printf("Sono stati caricati %d libri dal file binario.\n", count);
    }
    else
    {
        // Se il file binario non esiste, leggi i dati dal CSV
        count = leggi_csv("libreria_libri.csv", libri, MAX_LIBRI);
        if (count > 0)
        {
            printf("Sono stati letti %d libri dal file CSV.\n", count);
        }
        else
        {
            printf("Errore durante la lettura del file CSV.\n");
            return 1; // Esci in caso di errore
        }
    }

    // Mostra il menu all'utente
    menu(libri, count);

    return 0;
}
