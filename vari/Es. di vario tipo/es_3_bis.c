#include <stdio.h>

int main(int argc, char *argv[])
{

    int numeri[5];
    *(numeri) = 0;
    *(numeri + 1) = 10;
    *(numeri + 2) = 20;
    *(numeri + 3) = 30;
    *(numeri + 4) = 40;

    printf("Indirizzo dell'array numeri: %p\n", numeri);    // Stesso risultato ⌄
    printf("Indirizzo dell'array numeri: %p\n", &numeri);   // Stesso risultato ^
    printf("Indirizzo di numeri[0]: %p\n", numeri); // &(numeri[0]) mostra l'indirizzo del primo el. dell'array, che equivale all'indirizzo iniziale dell'array: numeri

    for (int i = 0; i < 5; i++)
    {
        printf("%p\n", numeri + i); // Stampa indirizzi
    }

    for (int i = 0; i < 5; i++)
    {
        printf("numeri[%d]: %d\n", i, *(numeri + i));   // Stampa contenuto array
    }
    return 0;
}