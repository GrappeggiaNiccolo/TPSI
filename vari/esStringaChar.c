#include <stdio.h>
#include <string.h>
int main()
{
    char str1[20], carattere;
    int contChar = 0;
    printf("Inserire una stringa: ");
    scanf("%c", str1);
    printf("Inserire il carattere: \n");
    //scanf("%c", &carattere);
    carattere = getchar();

    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] == carattere)
        {
            contChar++;
        }
    }

    if (contChar == 0)
    {
        printf("Il carattere %c non è presente\n", carattere);
    }
    else
    {
        printf("Il carattere %c è presente %d volte\n", carattere, contChar);
    }
    return 0;
}