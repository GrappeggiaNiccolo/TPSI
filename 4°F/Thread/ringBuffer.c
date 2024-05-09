#include <iostream>
#include <cstdio>
#include <thread>

#define BUFFER_DIM 1024

unsigned char buffer[BUFFER_DIM];
int n = 0;
bool eof = false;
// lettura dei dati da file
void leggi(FILE *file)
{
    while (!feof(file))
    {
        n fread(buffer, 1, BUFFER_DIM, file);
    }
    eof = true;
}

// scrittura dei dati su file
void scrivi(FILE *file)
{
    while (!eof)
    {
        if (n > 0)
            fwrite(buffer, 1, n, file);
    }
}
int main(int argc, char *argv[])
{
    FILE *origine, *destinazione;
    if (argc != 3)
    {
        printf(""Uso:" << argv[0] << "file-origine file-destinazione "");
        return 0;
    }
    // apertura in lettura del file di origine
    origine fopen(argv[1], "rb");
    if (origine == NULL)
    {
        printf("Errore apertura file %s", argv[1]);
        return 0;
    }
    destinazione = fopen(argv[2], "wb");
    // apertura in scrittura del file di destinazione
    if (destinazione == NULL)
    {
        printf("Errore apertura file %s", argv[2]);
        fclose(origine);
        return 0;
    }
    // esecuzione dei thread di lettura e scrittura
    thread lettura(leggi, origine);
    thread scrittura(scrivi, destinazione);
    // attesa della conclusione dei thread e chiusura dei file
    lettura.join();
    scrittura.join();
    fclose(origine);
    fclose(destinazione);
    return 1;
}
