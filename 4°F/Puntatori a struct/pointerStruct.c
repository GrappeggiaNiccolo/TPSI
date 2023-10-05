#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    typedef struct
    {
        char nome[20];
        char cognome[20];
        int media;
    } studente;

    studente stud;
    studente *std = (studente*)&stud; // cast??? --> non necessario

    strcpy(std->nome, "nome");
    strcpy(std->cognome, "conome");
    std->media = 8;

    printf("%s\n", std->cognome);
    printf("%s\n", std->nome);
    printf("%d\n", std->media);

    return 0;
}