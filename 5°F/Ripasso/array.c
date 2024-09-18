#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
/*Scrivere un programma in C che effettui, attraverso un menù, le seguenti operazione sugli array:
1) Visualizzi a video gli elementi dell’array inseriti o generati casualmente;
2) Visualizzi a video l’array invertito cioè sostituendo il primo elemento con l&#39;ultimo , il secondo con il
penultimo e cosi via;
3) Visualizzi a video la somma e media degli elementi del vettore;
4) Visualizzi a video tutti i numeri pari;
5) Visualizzi a video tutti i numeri dispari;
6) Ricerchi un numero (letto in input) nell’array;
7) Elimini un elemento (letto in input) dell’array (se esistente);
8) Alterni (o scambi ) a due a due le posizioni del vettore: esempio
vettore: 1,2,3,4 vettore alternato: 2,1,4,3 (attenzione se lungo dispari);
9) Ordini il vettore (ordinamento a scelta).*/

int Menu()
{
    int scelta;

    // Opzioni menu
    printf("0) Esci\n");
    printf("1) Visualizzi a video gli elementi dell’array generati casualmente\n");
    printf("2) Visualizzi a video l’array invertito cioè sostituendo il primo elemento con l'ultimo , il secondo con il penultimo e cosi via\n");
    printf("3) Visualizzi a video la somma e media degli elementi del vettore;\n");
    printf("4) Visualizzi a video tutti i numeri pari;\n");
    printf("5) Visualizzi a video tutti i numeri dispari;\n");
    printf("6) Ricerchi un numero (letto in input) nell’array;\n");
    printf("7) Elimini un elemento (letto in input) dell’array (se esistente);\n");
    printf("8) Alterni (o scambi ) a due a due le posizioni del vettore: esempio vettore: 1,2,3,4 vettore alternato: 2,1,4,3 (attenzione se lungo dispari);\n");
    printf("9) Ordini il vettore (ordinamento a scelta)\n\n");
    // scelta utente
    scanf("%d", &scelta);
    return(scelta);
}

void Visualizza()
{
    int n;
    printf("Premere invio per tornare al menu");
    scanf("%d", &n);
    Menu();
}

void ChiamaFunzione(int scelta) {
    switch (scelta)
    {
    case 0:
        exit(0);
        break;
    case 1:
        Visualizza();
        break;
    }
}

int main(int argc, char *argv[])
{
    int arrLength;
    printf("Quanti elementi inserire nell'array? ");
    scanf("%d", &arrLength);

    int array[arrLength];

    // Menù e scelta
    ChiamaFunzione(Menu());

    return 0;
}