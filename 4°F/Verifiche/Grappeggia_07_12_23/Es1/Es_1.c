#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Argomenti non sufficienti");
        return -1;
    }

    FILE *file;
    char nome[20];
    strcpy(nome, argv[1]);
    char stringa[20];
    strcpy(stringa, argv[2]);

    file = fopen(nome, "w");

    fputs(stringa, file);
    fclose(file);

    file = fopen(nome, "r");
    //char ch = fgetc(file);
    //printf("%c\n\n", ch);


    char ch;
    int i;
    while ((ch = fgetc(file)) != EOF) 
    {
        if (i == 1)
        {
            putchar(ch);
            printf("\n\n");
        }
        i++;
    }

    fclose(file);

    return 0;
}