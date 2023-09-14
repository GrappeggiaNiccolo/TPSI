#include <stdio.h>
#include <string.h>
int main()
{
    char str1[20], str2[20], carattere;
    int contDoppie = 0;
    printf("Inserire una stringa: ");
    scanf("%s", str1);


    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i + 1] == str1[i]) //strcmp(str1[i + 1], str1[i]) == 0
        {
            contDoppie++;
        }
    }

    if (contDoppie == 0)
    {
        printf("Non ci sono doppie\n");
    }
    else
    {
        printf("Compaiono doppie %d volte\n", contDoppie);
    }
    return 0;
}