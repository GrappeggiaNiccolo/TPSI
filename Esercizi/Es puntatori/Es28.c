#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Funzione(char str1[], char str2[])
{
    char *p = str2;
    for (int i = 0; i < strlen(str1); i++)
    {
        if (isdigit(str1[i]))
        {
            *p = str1[i];
            p++;
        }
    }
}

int main(int argc, char *argv[])
{
    char str1[100], str2[100] = {0};
    printf("inserire la stringa: ");
    scanf("%s", str1);

    Funzione(str1, str2);

    if (str2[0] != 0)
        printf("\nstr2: %s\n", str2);
    else
        printf("\nNon ci sono numeri nella stringa\n");

    return 0;
}