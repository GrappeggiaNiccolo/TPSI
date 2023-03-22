// Scrivere un programma in C che dopo aver inserito N numeri interi in un vettore,
// alterni (o scambi ) a due a due le posizioni del vettore. Esempio:
// vettore inserito: 1,2,3,4  vettore alternato: 2,1,4,3.
#include <stdio.h>
#include <string.h>
int main()
{
    int N, i = 0, scambio;
    char numero;

    printf("Quanti numeri vuoi inserire? ");
    scanf("%d", &N);
    int vett[N];

    for (i = 0; i < N; i++)
    {
        printf("Inserire il %d° numero ", i + 1);
        scanf("%d", vett + i);
    }

    for (i = 0; i < N; i += 2)
    {
        scambio = vett[i];
        vett[i] = vett[i + 1];
        vett[i + 1] = scambio;
    }

    for (i = 0; i < N; i++)
    {
        printf("%d", vett[i]);
    }
    
    return 0;
}