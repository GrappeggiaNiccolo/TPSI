#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LENGTH 1000
#define NUM 8
typedef struct Valori
{

};

void *cerca1(void *array)
{
    for (int i = 0; i < LENGTH / 2; i++)
    {
        if (((int *)array)[i] == NUM)
        {
            printf("Prima metà - Il numero %d si trova nella posizione %d\n", NUM, i);
        }
    }
    return NULL;
}

void *cerca2(void *array)
{
    for (int i = LENGTH / 2; i < LENGTH; i++)
    {
        if (((int *)array)[i] == NUM)
        {
            printf("Seconda metà - Il numero %d si trova nella posizione %d\n", NUM, i);
        }
    }
    return NULL;
}
void Inserimento(void *arr)
{
    for (int i = 0; i < LENGTH; i++)
    {
        ((int *)arr)[i] = rand(); // uso la funzione random per generare numeri casuali
    }
}
int main(int argc, char *argv[])
{
    int arr[LENGTH], *inizio, *fine;
    srand(time(NULL)); // inizializza il random
    pthread_t t1, t2;

    Inserimento((void *)&arr);
    arr[6] = 8;

    pthread_create(&t1, NULL, &cerca1, (void *)&arr);
    pthread_create(&t2, NULL, &cerca2, (void *)&arr);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}