#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

#define LENGTH 20
/*Scrivere un programma in C che dopo aver inserito una stringa a piacere determini e o verifichi:

1) Che contenga solo lettere;
2) Il conteggio di una lettera (se presente) scelta dall’utente;
3) Crei 2 ulteriori stringhe che contengano 1 le lettere di posizione pari; la 2° le lettere di posizione
dispari;
4) Verifichi se contiene doppie.

Inserita una 2° stringa determinare:
1) Quale delle 2 è più lunga e più corta;
2) Quali sono le lettere contenute in ambedue le stringhe;
3) Quale delle 2 stringhe contiene più vocali;
4) Quale delle 2 stringhe contiene più consonanti;*/

int ControlloLettere(char stringa1[])
{
    for (int i = 0; i < strlen(stringa1); i++)
    {
        if (!isalpha(stringa1[i]))
        {
            return 1;
        }
    }
    return 0;
}

int ContaLettera(char stringa1[], char c)
{
    int cont = 0;

    for (int i = 0; i < strlen(stringa1); i++)
    {
        if (stringa1[i] == c)
        {
            cont++;
        }
    }

    return cont;
}

int main(int argc, char *argv[])
{
    char stringa1[LENGTH], stringa2[LENGTH];

    // inserimento stringa
    printf("Inserire una stringa: ");
    scanf("%s", stringa1);

    // 1)
    if (ControlloLettere(stringa1))
    {
        printf("\n1) la stringa 1 contiene numeri\n");
    }
    else
    {
        printf("\n1) La stringa 1 non contiene numeri\n");
    }
    // 2)
    char c;
    printf("\nInserire una lettera da ricercare nella stringa: ");
    scanf(" %c", &c);

    int num = ContaLettera(stringa1, c);
    printf("\n2) La stringa 1 contiene la lettera '%c' %d volte\n", c, num);

    // 3)
    char PariDispari[2];

    return 0;
}