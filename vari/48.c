#include <stdio.h>
void main()
{ // Dopo aver letto N numeri reali calcolare la somma e la media degi numeri compresi tra 4 e 8
  // estremi inclusi visualizzando a video i risultati
  float num, somma = 0, media;
  int n, cont = 0, cont2 = 0;
  printf("Quanti numeri vuoi inserire?\n");
  scanf("%d", &n);
  while (cont < n)
  {
    printf("Inserisci il %d numero: \n", cont + 1);
    scanf("%f", &num);
    cont++;
    if (num >= 4 && num <= 8)
    {
      somma = somma + num;
      cont2++;
    }
  }
  if (somma > 0)
  {
    media = somma / cont2;
    printf("la somma è %.2f\n", somma);
    printf("la media è %.2f\n", media);
  }
  else
  {
    printf("I numeri non sono compresi fra 4 e 8\n");
  }
}