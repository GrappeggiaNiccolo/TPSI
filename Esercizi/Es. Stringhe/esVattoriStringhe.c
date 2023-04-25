// Scrivere un programma in C che dopo aver inserito N numeri interi in un vettore,
// alterni (o scambi ) a due a due le posizioni del vettore. Esempio:
// vettore inserito: 1,2,3,4  vettore alternato: 2,1,4,3.
//     strcpy(str1, argv[1]);

#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int i = 0, scambio; // dichiaro le variabili
    int vett[4]; // inserisco la lunghezza dell'array da argv[1]

    for (i = 0; i < 5; i++)
    {
        printf("Inserire il %d° numero ", i + 1);
        scanf("%d", vett + i);
    }

    for (i = 0; i < 5 - 1; i += 2)
    {
        scambio = vett[i];
        vett[i] = vett[i + 1];
        vett[i + 1] = scambio;
    }

    for (i = 0; i < 5; i++)
    {
        printf("%d", vett[i]);
    }

    return 0;
}