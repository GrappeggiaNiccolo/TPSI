// scrivere programma che effettui somma di due numeri interi
// bisogna dichiarare variabili all'inizio
#include <stdio.h> //librerie
void main()        // entry point
{
    // dichiarazione variabili
    int add1, add2, somma1;   // int = intero
    float var1, var2, somma2; // float = n° reale
    add1 = 50;
    add2 = 80;
    var1 = 3.50;
    var2 = 5.50;
    somma1 = add1 + add2;
    printf("La somma e': %d ", somma1); // d = decimal; % dice che tipo di variabile f= float = reale

    somma2 = var1 + var2;
    printf("La somma e': %.2f ", somma2); // .2 --> stampa solo 2 decimali

    scanf("Ciao");
}