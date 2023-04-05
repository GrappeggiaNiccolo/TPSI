#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[])
//     Scrivere un programma in C che dopo aver inserito una stringa a piacere determini e o verifichi:

// 1)      Che contenga solo lettere;
// 2)      Crei 2 ulteriori stringhe che contengano: la 1° le lettere di posizione pari; la 2° le lettere di posizione dispari;
//
//     Inserita una 2° stringa determinare:
// 1)      Quale delle 2 è più lunga e più corta;
// 2)      Quale delle 2 stringhe contiene più vocali;
// 3)      Quale delle 2 stringhe contiene più consonanti.
{
    int k = 0, contVoc, contDisp;
    char str[50], pari[50], disp[50];

    printf("Inserire una stringa: ");
    scanf("%s", str);

    // 1) Che contenga solo lettere;
    do
    {
        if (!isalpha(str[k]))
        {
            printf("La stringa non deve essere numerica/alfanumerica \n");
            return 0;
        }
        k++;
    } while (str[k] != '\0');
    k = 0;

    // 2) Crei 2 ulteriori stringhe che contengano: la 1° le lettere di posizione pari; la 2° le lettere di posizione dispari;
    for (int i = 0; i < strlen(str) && str[i] != '\0'; i++)
    {
        if (str[i] != '\0')
        {
            if (i % 2 == 0)
            {
                pari[contVoc] = str[i];
                contVoc++;
            }
            else
            {
                disp[contDisp] = str[i];
                contDisp++;
            }
        }
    }

    for (int i = 0; i < strlen(pari); i++)
    {
        printf("%s", pari);
    }

    // 3) Quale delle 2 è più lunga e più corta;

    return 0;
}