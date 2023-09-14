#include <stdio.h>
void main()
{
    /*Dopo aver letto in input il valore di un lato di un quadrato calcolare il perimetro e l’area, visualizzando a
    video i risultati.*/
    int lato, perimetro, area;
    printf("Inserire un lato del quadrato\n");
    scanf("%d", &lato);
    area = lato ^ 2;
    perimetro = lato * 4;
    printf("Il perimetro è di %d\n", perimetro);
    printf("L'area è di %d\n", area);
}