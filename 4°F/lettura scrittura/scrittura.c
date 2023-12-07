#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{                                           // bisogna creare un puntatore a file
    FILE *puntaFile;                        // struttura per lettura e scrittura file
    puntaFile = fopen("nomeFile.txt", "r"); // lettura

    if (puntaFile == NULL)
    {
        printf("FIle non accessibile");
        fclose(puntaFile);
        return -1;
    }

    printf("File %s aperto", puntaFile);



    return 0;
}