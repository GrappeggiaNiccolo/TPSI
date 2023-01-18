#include <stdio.h>
void main()
{
    // Scrivere un programma in c che dopo aver acquisito da tastiera un elenco di prezzi relativi alle vendite di N
    // prodotti ed il relativo percentuale del prezzo secondo una percentuale, visualizzi a video:
    // 1) Il prezzo incrementato per ogni inserimento effettuato;
    // 2) Il totale e la media dei prezzi incrementati;
    // 3) La media dei prezzi incrementati maggiori di 50€;
    int prodotti, cont = 0;
    float percentuale, prezzo, media, totale = 0, media50 = 0, prezzoIncremento, totale50 = 0;

    printf("Quanti prodotti devono essere venduti?\n");
    scanf("%d", &prodotti);

    if (prodotti <= 0)
    {
        do
        {
            printf("Quantità non valida\n");
            printf("Quanti prodotti devono essere venduti?\n");
            scanf("%d", &prodotti);
        } while (prodotti <= 0);
    }

    for (int i = 1; i <= prodotti; i++)
    {
        // Inserimento del prezzo del prodotto, con controllo se il valore inserito è accettabile
        printf("Qual'è il prezzo del %d° prodotto?\n", i);
        scanf("%f", &prezzo);
        if (prezzo <= 0)
        {
            do
            {
                printf("Quantità non valida\n");
                printf("Qual'è il prezzo del %d° prodotto?\n", i);
                scanf("%f", &prezzo);
            } while (prezzo <= 0);
        }
        // Inserimento dell'percentuale del prodotto, con controllo se il valore inserito è accettabile
        printf("Qual'è l'incremento percentuale del %d° prodotto? (in percentuale)\n", i);
        scanf("%f", &percentuale);
        if (percentuale <= 0)
        {
            do
            {
                printf("Quantità non valida\n");
                printf("Qual'è l'percentuale del %d° prodotto? (in percentuale)\n", i);
                scanf("%f", &percentuale);
            } while (percentuale <= 0);
        }
        // Calcolo prezzi scontati, totale
        prezzoIncremento = prezzo + prezzo * (percentuale / 100);
        printf("\nIl prezzo incrementato è di %.2f €", prezzoIncremento);
        totale = totale + prezzoIncremento;
        media = totale / i;
        if (prezzoIncremento > 50)
        {
            cont++;
            totale50 = totale50 + prezzoIncremento;
            media50 = prezzoIncremento / cont;
        }
    }
    // Stampo il totale dei prezzi scontati
    printf("\nIl totale dei prezzi scontati è di %.2f €", totale);
    printf("\nLa media è di %.2f €", media);
    printf("\nLa media dei numeri maggiori di 50 è di %.2f €", media50);
}