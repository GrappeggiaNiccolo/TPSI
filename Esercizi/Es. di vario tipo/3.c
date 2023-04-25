// scrivere programma che effettui somma di due numeri interi
// bisogna dichiarare variabili all'inizio
#include <stdio.h> //librerie
void main()        // entry point
{
    // dichiarazione variabili
    int add1, add2, somma1, diff, prod, contatore = 0; // int = intero
    float var1, var2, somma2, quoz1;                   // float = n° reale
    add1 = 50;
    add2 = 80;
    var1 = 3.50;
    var2 = 5.50;
    somma1 = add1 + add2;
    printf("La somma intera e': %d ", somma1); // d = decimal; % dice che tipo di variabile f= float = reale

    somma2 = var1 + var2;
    printf("La somma decimale e': %.2f  \n", somma2); // .2 --> stampa solo 2 decimali

    quoz1 = var1 / var2; // quoziente fra numeri reali
    printf("Il quoziente fra reali e': %.2f ", quoz1);

    quoz1 = (float)add2 / add1; // casting = serve per fare il quoziente fra numeri interi
    printf("Il quoziente fra interi e': %.2f \n", quoz1);

    diff = add1 - add2; // differenza fra numeri interi
    printf("La differenza e': %d  \n", diff);

    prod = add1 * add2; // prodotto
    printf("Il prodotto fra interi e': %d \n", prod);

    contatore++; // aggiungo 1 al contatore (0+1)
    printf("Il risultato del contatore e': %d \n", contatore);

    scanf("Ciao");
}