#include <stdio.h>

int Array()
{
    int n;

    do
    {
        printf("Quanti numeri desidera inserire?");
        scanf("%d", &n);
    } while (n < 0);

    return n;
}

void Inserimento(int n, int numeri[])
{
    int cont = 0;
    do
    {
        printf("Inserire il %d° numero: ", cont + 1);
        scanf("%d", &numeri[cont]);

        while (numeri[cont] < 0 || numeri[cont] > 9)
        {
            printf("Inserimento errato, inserire un altro numero:\n");
            scanf("%d", &numeri[cont]);
        }

        cont++;
    } while (cont < n);
}

void Verifica(int n, int numeri[], int ripetuto[])
{
    for (int i = 0; i < n; i++)
    {
        ripetuto[numeri[i]]++;
    }
}

void Stampa(int ripetuto[])
{
    int max = -1;

    for (int i = 0; i < 10; i++)
    {
        if (ripetuto[i] > max)
        {
            max = ripetuto[i];
        }
    }

    printf("\nIl numero %d si ripete più volte\n", max);

}

int main(int argc, char *argv[])
{
    int n = Array(), numeri[n], ripetuto[10];

    Inserimento(n, numeri); // funzione per inserire i numeri nell'array

    Verifica(n, numeri, ripetuto);

    Stampa(ripetuto);

    return 0;
}
