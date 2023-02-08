#include <stdio.h>
void main()
{
    char str[30];
    int i = 0;
    printf("Inserisci una stringa: ");
    scanf("%s", str); // non si usa & perchè è un array
    printf("\nHai inserito la segurnte stringa %s", str);
    while (str[i] != '\0')
    {
        i++;
    }
    printf("\nLa stringa è lunga %d caratteri", i);
}