// Scrivere un programma in C che dopo aver inserito una stringa crei 2 ulteriori stringhe contenenti,
// la prima i caratteri speciali e la seconda lettere ordinate in ordine alfabetico.
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int i = 0, contChar = 0, contLett = 0;
    char str1[50], str2[50], str3[50], temp;
    printf("Inserire la stringa: \n");
    scanf("%s", str1);
    // Separo lettere da caratteri speciali usando l tabella ASCII
    // ASCII: 65 - 90 maiuscole; 97 - 122 minuscole
    do
    {
        if ((str1[i] >= 65 && str1[i] <= 90) || (str1[i] >= 97 && str1[i] <= 122))
        {
            if (str1[i] >= 65 && str1[i] <= 90)
            {
                str1[i] += 32;
            }
            str2[contLett] = str1[i];
            contLett++;
        }
        else
        {
            str3[contChar] = str1[i];
            contChar++;
        }
        i++;
    } while (i < strlen(str1) && str1[i] != '\0');

    // Ordino in ordine alfabetico la stringa di letere ottenuta
    for (int j = 0; j < strlen(str2) - 1; j++)  // && (str2[j] != '\0')
    {
        for (int k = 0; k < strlen(str2) - 1 - j; k++)
        {
            if (str2[k] > str2[k + 1])
            {
                temp = str2[k];
                str2[k] = str2[k + 1];
                str2[k + 1] = temp;
            }
        }
    }

    printf("%s \n", str2);
    printf("%s \n", str3);

    return 0;
}