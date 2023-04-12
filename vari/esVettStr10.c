// Scrivere un programma in C che dopo aver inserito 2 stringhe visualizzi a video le lettere comuni ad entrambe.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
    int cont = 0;
    char str1[50], str2[50];
    // Inserimento prima stringa
    printf("Inserire la prima stringa: ");
    scanf("%s", str1);
    // Verifico che contenga solo lettere
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] < 'a' || str1[i] > 'z')
        {
            printf("La stringa non deve essere numerica/alfanumerica \n");
            return 0;
        }
    }
    // Caratteri minuscoli
    for (int i = 0; i < strlen(str1); i++)
    {
        str1[i] = tolower(str1[i]);
    }

    // Inserimento seconda stringa
    printf("Inserire la seconda stringa: ");
    scanf("%s", str2);
    // Verifico che contenga solo lettere
    for (int i = 0; i < strlen(str2); i++)
    {
        if (str2[i] < 'a' || str2[i] > 'z')
        {
            printf("La stringa non deve essere numerica/alfanumerica \n");
            return 0;
        }
    }
    // Caratteri minuscoli
    for (int i = 0; i < strlen(str2); i++)
    {
        str2[i] = tolower(str2[i]);
    }

    for (int i = 0; i < strlen(str1); i++)
    {
        for (int k = 0; k < strlen(str2) && cont < 1; i++)
        {
            if (str1[i] == str2[k])
            {
                printf("%c\n", str1[i]);
                cont++;
            }
        }
    }

    return 0;
}