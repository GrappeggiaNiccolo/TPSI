#include <stdio.h>

typedef struct Punto
{
    int x, y, z;
} Punto;

void stampa_punto(Punto punto)
{
    printf("\nx: %d, y: %d, z: %d\n", punto.x, punto.y, punto.z);
}

Punto punto_modificato(Punto punto)
{
    Punto modificato = {punto.x + 1, punto.y + 1, punto.z + 1};

    return modificato;
}

int main(int argc, char *argv[])
{
    Punto punto;

    printf("Inserisci la coordinata X del punto: ");
    scanf("%d", &punto.x);
    printf("Inserisci la coordinata Y del punto: ");
    scanf("%d", &punto.y);
    printf("Inserisci la coordinata Z del punto: ");
    scanf("%d", &punto.z);

    stampa_punto(punto);

    Punto modificato = punto_modificato(punto);

    stampa_punto(modificato);

    return 0;
}