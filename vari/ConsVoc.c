#include <stdio.h>
#include <string.h>
void main()
{                                                // Scrivere un programma che dopo aver inserito una stringa conti le consonanti e le vocali
    int i, cons = 0, voc = 0, lung = 0, num = 0; // Contatori
    char str[20];
    printf("Inserisci la stringa: ");
    scanf("%s", str); // Le stringhe non necessitano l'uso di &
    while (str[i] != '\0')
    {
        i++;
        // lung++;
    }
    lung = i;

    for (i = 0; i < lung; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            voc++;
        }
        else if (str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9' || str[i] == '0')
        {
            num++;
        }
        else
        {
            cons++;
        }
    }
    printf("Consonanti: %d\n", cons);
    printf("Vocali: %d", voc);
}