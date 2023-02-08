#include <stdio.h>
void main()
{
    float bev, rist, mediaB, mediaR, totB = 0, totR = 0;
    int contB = 0, contR = 0;
    string esci = "";
    string consumazione = "";
    do
    {
        printf("\nInserire il tipo di consumazione(bevanda/ristorazione): ");
        scanf("%s", &consumazione);
        if (consumazione == "bevanda")
        {
            contB++;
            printf("\nInserisca l'importo della bevanda: ");
            scanf("%f", &bev);
            totB = totB + bev;
        }
        else if (consumazione == "ristorazione")
        {
            contB++;
            printf("\nInserisca l'importo della ristorazione: ");
            scanf("%f", &rist);
            totR = totR + rist;
        }
        else
        {
            printf("\nErrore d'inserimento");
        }
        printf("\nDesidera continuare?(si/no) ");
        scanf("%s", &esci);
    } while (esci == "no");

    // Risultati
    mediaB = totB / contB;
    mediaR = totR / contR;
    printf("\nLa media delle bevande è di: ", mediaB);
    printf("\nLa media delle ristorazioni è di: ", mediaR);
    if (contB > contR) 
    {
        printf("\nSono state vendute più bevande");
    }
    else
    {
        printf("\nSono state vendute più ristorazioni");
    }

}