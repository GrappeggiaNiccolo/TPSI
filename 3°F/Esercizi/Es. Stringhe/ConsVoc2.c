#include <stdio.h>
#include <string.h>
void main()
{
    int i = 0, lung;
    char str1[40], str2[20];
    printf("Inserisci la prima stringa: ");
    scanf("%s", str1);
    lung = strlen(str1);
    printf("La lunghezza della stringa è %d", lung);

    printf("\nInserisci la seconda stringa: ");
    scanf("%s", str2);
    lung = strlen(str2);
    printf("La lunghezza della stringa è %d\n", lung);

    // Confronto le due stringhe
    if (strcmp(str1, str2) == 0)
    {
        printf("Le stringhe sono uguali");
    }
    else
    {
        printf("Le due stringhe sono diverse\n");
        strcat(str1, str2); // Somma le due stringhe in str1
        printf("La somma delle stringhe è: %s\n", str1);
        strcpy(str1,str2);  // copia in str1 str2
        printf("La stringa copiata è: %s\n", str1);
    }
}