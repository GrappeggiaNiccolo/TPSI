#include <stdio.h>
#include <stdlib.h>

#define LIBRI 2

typedef struct
{
    char *titolo[20];
    char *autore[20];
    float prezzo;
} biblioteca;

void Inserimento(biblioteca *libri, int i)
{
    printf("Inserire il titolo del %d° libro: ", i + 1);
    scanf("%s", libri->titolo);
    printf("Inserire l'autore del %d° libro: ", i + 1);
    scanf("%s", libri->autore);
    printf("Inserire il prezzo del %d° libro: ", i + 1);
    scanf("%f", &libri->prezzo);
}

void Print(biblioteca **libri)
{
    for (int i = 0; i < LIBRI; i++)
    {
        printf("Libro %d\n", i + 1);
        printf("Titolo: %s\n", libri[i]->titolo);
        printf("Autore: %s\n", libri[i]->autore);
        printf("prezzo: %.2f\n", libri[i]->prezzo);
        printf("\n");
    }
}

void Discount(biblioteca **libri, int *sconto)
{
    for (int i = 0; i < LIBRI; i++)
    {
        libri[i]->prezzo -= libri[i]->prezzo / 100 * *sconto;
    }
}
int main(int argc, char *argv[])
{
    biblioteca *libri[LIBRI];
    int sconto;
    for (int i = 0; i < LIBRI; i++)
    {
        libri[i] = (biblioteca *)malloc(sizeof(biblioteca));
        Inserimento(libri[i], i);
        printf("\n");
    }

    Print(libri);

    printf("Inserire lo sconto: ");
    scanf("%d", &sconto);
    printf("\n");

    Discount(libri, &sconto);

    Print(libri);

    return 0;
}