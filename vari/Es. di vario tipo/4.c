#include <stdio.h>
void main()
{ // if && if else && else if
    // letti due numeri determina il maggiore
    int num1, num2, max, min;
    printf("Inserisci il primo numero \n");
    scanf("%d", &num1);
    printf("Inserisci il secondo numero \n");
    scanf("%d", &num2);
    if (num1 > num2)
    {
        max = num1;
        min = num2;
        printf("Il numero maggiore è %d\n", max);
        printf("il numero minore è %d\n", min);
    }
    else if (num1 < num2)
    {
        max = num2;
        min = num1;
        printf("Il numero maggiore è %d\n", max);
        printf("il numero minore è %d\n", min);
    }
    else
    {
        printf("I numeri %d e %d sono uguali\n", num1, num2);
    }
}