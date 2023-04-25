#include <stdio.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    int vett[100], n, pari[100], disp[100], k = 0, t = 0, max_pari, min_pari, max_disp, min_disp;

    do
    {
        printf("Inserire lunghezza vettore: ");
        scanf("%d", &n);
    } while (n < 1 || n > 100);

    for (int i = 0; i < n; i++)
    {
        printf("Inserire %d° elemento vettore: ", i + 1);
        scanf("%d", &vett[i]);
    }

    return 0;
}