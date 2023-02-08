#include <stdio.h>
int main()
{
    char carattere;
    printf("inserisci carattere: ");
    //scanf("%c", &carattere);
    carattere = getchar();
    printf("Hai inserito il seguente carattere: %c ", carattere);
    putchar(carattere);
    printf("\nIl codice ascii del carattere inserito %d", carattere);
}