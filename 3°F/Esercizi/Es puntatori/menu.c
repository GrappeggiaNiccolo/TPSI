#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

int Array(int numeri[])
{
    int cont = 0;
    while (1)
    {
        printf("Inserire il %d° numero: ", cont + 1);
        scanf("%d", &numeri[cont]);

        while (numeri[cont] < -1)
        {
            printf("Inserimento errato, inserire un altro numero:\n");
            scanf("%d", &numeri[cont]);
        }

        if (numeri[cont] == -1)
        {
            return cont;
        }
        cont++;
    }
}
int Opzione()
{
    int opzione = 0;
    do
    {
        int crlscr(); // $ clear

        printf("\n[0] termina il programma");
        printf("\n[1] mostrare il contenuto dell'array");
        printf("\n[2] inserire un elemento in coda");
        printf("\n[3] modificare un elemento se presente");
        printf("\n[4] eliminare un elemento se presente");
        printf("\n[5] ricercare un elemento");
        printf("\n[6] inserire un elemento in una certa posizione");
        printf("\n[7] mostrare il contenuto dell'array all'inverso");
        printf("\n[8] mostrare il valore massimo dell'array\n");
        printf("fai la tua scelta:\n");
        scanf("%d", &opzione);
    } while (opzione < 0 || opzione > 8);

    return opzione;
}
void Mostra_Numeri(int n, int numeri[]) // 1
{
    for (int i = 0; i < n; i++)
    {
        printf("\nIl valore in posizione %d è: %d", i + 1, numeri[i]);
    }
}
void Inserimento_Elemento(int NumInCoda, int n, int numeri[]) // 2
{
    printf("inserisci un numero da mettere in coda:\n");
    scanf("%d", &NumInCoda);
    for (int i = 0; i < n; i++)
    {
        if (numeri[i] == 0)
        {
            numeri[i] = NumInCoda;
            break;
        }
        else
        {
            printf("\nL'array è pieno");
        }
    }
}
int Modifica_Elemento(int n, int numero, int sostituto, int numeri[]) // 3
{
    printf("inserisci un numero da modificare:\n");
    scanf("%d", &numero);
    for (int i = 0; i < n; i++)
    {
        if (numeri[i] == numero)
        {
            printf("inserisci il numero che andrà a sostituire il numero selezionato:\n");
            scanf("%d", &sostituto);
            sostituto = numeri[i];
        }
        else
        {
            printf("il numero non è presente nell'array");
        }
    }
}
void Elimina_Elemento(int n, int elimina, int numeri[]) // 4
{
    printf("inserisci un numero da eliminare:\n");
    scanf("%d", &elimina);
    for (int i = 0; i < n; i++)
    {
        if (numeri[i] == elimina)
        {
            do
            {
                numeri[i] = numeri[i + 1];
                i++;
            } while (i < n);
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("Il valore in posizione %d è: %d\n", i + 1, numeri[i]);
    }
}
void Ricerca_Elemento(int n, int ricerca, int numeri[]) // 5
{
    printf("inserisci il numero che vuioi ricercare:\n");
    scanf("%d", &ricerca);
    for (int i = 0; i < n; i++)
    {
        if (ricerca == numeri[i])
        {
            printf("il numero ricercato si trova in posizione %d°", i + 1);
        }
    }
}
void Inserimento_Nuovo_Elemento(int n, int posizione, int numero, int numeri[]) // 6
{
    printf("scegli un numero da inserire:\n");
    scanf("%d", &numero);
    printf("scegli in che posizione inserire il numero scielto:\n");
    scanf("%d", &posizione);
    numeri[posizione] = numero;
    for (int i = 0; i < n; i++)
    {
        printf("\nIl valore in posizione %d è: %d", i + 1, numeri[i]);
    }
}
void Mostra_Numeri_Reverse(int n, int numeri[]) // 7
{
    for (int i = n - 1; i >= 0; i--)
    {
        printf("\nIl valore in posizione %d è: %d\n", i, numeri[i]);
    }
}
void Mostra_Valore_Massimo(int n, int max, int numeri[]) // 8
{
    max = numeri[0];
    for (int i = 1; i < n; i++)
    {
        if (numeri[i] > max)
        {
            max = numeri[i];
        }
    }
    printf("il valore massimo è %d", max);
}
void Azione(int n, int opzione, int numeri[])
{
    if (opzione == 1)
    {
        Mostra_Numeri(n, numeri); // 1
    }
    if (opzione == 2)
    {
        int NumInCoda;
        Inserimento_Elemento(n, NumInCoda, numeri); // 2
    }
    if (opzione == 3)
    {
        int Modifica_Elemento(int n, int nuemro, int sostituto, int numeri[]); // 3
    }
    if (opzione == 4)
    {
        int elimina;
        Elimina_Elemento(n, elimina, numeri); // 4
    }
    if (opzione == 5)
    {
        int ricerca;
        Ricerca_Elemento(n, ricerca, numeri); // 5
    }
    if (opzione == 6)
    {
        int posizione;
        int numero;
        Inserimento_Nuovo_Elemento(n, posizione, numero, numeri); // 6
    }
    if (opzione == 7)
    {
        Mostra_Numeri_Reverse(n, numeri); // 7
    }
    if (opzione == 8)
    {
        int max;
        Mostra_Valore_Massimo(n, max, numeri); // 8
    }
}
int main()
{
    int numeri[SHRT_MAX], n = Array(numeri);
    do
    {
        int opzione = Opzione();
        if (opzione == 0)
        {
            printf("Programma finito");
            return 0;
        }
        else
        {
            Azione(n, opzione, numeri);
        }
    } while (1);
}
