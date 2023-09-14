#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 3)  // Controllo inserimento
    {
        printf("Errore argomenti \n");
        return 0;
    }

    int cont = 0;
    char str[30];

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] != argv[2][0])
        {
            str[cont] = argv[1][i];
            cont++;
        }
    }
    printf("\n%s \n", str);

    return 0;
}