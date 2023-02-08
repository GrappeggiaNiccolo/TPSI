#include <stdio.h>
void main()
{ /* Dopo aver letto in input i valori della base e dell’altezza di un rettangolo calcolare il perimetro e l’area,
   visualizzando a video i risultati .*/
     int base, altezza, perimetro, area;
     printf("Inserire la base del rettangolo\n");
     scanf("%d", &base);
     printf("Inserire l'altezza del rettangolo\n");
     scanf("%d", &altezza);
     area = base * altezza;
     perimetro = base * 2 + altezza * 2;
     printf("Il perimetro è di %d\n", perimetro);
     printf("L'area è di %d\n", area);
}