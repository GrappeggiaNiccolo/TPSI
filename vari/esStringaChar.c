#include <stdio.h>
#include <string.h>
int main()
{
    char str1[20],str2[20], carattere[1];
    int contChar = 0;
    printf("Inserire una stringa: ");
    scanf("%s", str1);

    strcpy(str2,str1);  //???

    printf("Inserire il carattere: \n");
    scanf("%s", carattere);
    //carattere = getchar();
    printf("%s", str2);
    printf("%s\n", carattere);
    for (int i = 0; i < strlen(str2); i++)
    {
        if (str2[i] == carattere[0])
        {
            contChar++;
        }
    }

    if (contChar == 0)
    {
        printf("Il carattere %c non è presente %d\n", carattere[0], contChar);
    }
    else
    {
        printf("Il carattere %c è presente %d volte\n", carattere[0], contChar);
    }
    return 0;
}