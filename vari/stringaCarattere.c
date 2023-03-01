// Leggi una stringa e un carattere e,
// se il carattere è presente nella stringa, conta quante volte quel carattere è contenuto nella stringa.
#include <stdio.h>
#include <string.h>
int main()
{
    int cont = 0, i = 0;
    char str[30], carattere[1];
    printf("Inserisci una stringa: ");
    scanf("%s", str); // non si usa & perchè è un array
    printf("Inserisci un carattere: ");
    scanf("%s", &carattere);
    
    printf("\nHai inserito la seguente stringa %s", str);
    printf("\nHai inserito il seguente carattere %s", carattere);
    while (i = 0; )
    {
        if (str[i] = carattere[0])
        {
            cont++;
        }
        i++;
    }
    printf("\nLa stringa è lunga %d caratteri", i);
    printf("\nIl carattere %s appare %d volte", carattere, cont);
    return 0;
}