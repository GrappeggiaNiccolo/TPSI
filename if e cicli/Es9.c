#include <stdio.h>

{
    int a, b, c;
    int min = 4294967295, max = 0;

    do
    {
        printf("\nInserisci A\n");
        scanf("%d", &a);
        printf("Inserisci B\n");
        scanf("%d", &b);
        printf("Inserisci C\n");
        scanf("%d", &c);

        if (c > b && b > a)
        {

            if (a < min)
                min = a;
            if (c > max)
                max = c;
        }
        else
        {
            printf("terna non valida\n");
        }

    } while (a >= 0 && b >= 0 && c >= 0);

    printf("\nNumero massimo: %d", max);
    printf("\nNumero minimo: %d", min);
}