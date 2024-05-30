/*in linguaggio c creare 2 thread, il primo genera una sequenza di N numeri casuali,
 con N fornito come argomento della riga di comando, e li inserisce singolarmente in un ring-buffer,
  il secondo preleva i numeri dal ring-buffer condiviso e li visualizza.
la codifica dovrà prevedere la necessaria sincronizzazione fra thread consumatore e thread produttore.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define BUFFER_SIZE 16

int ring_buffer[BUFFER_SIZE];
bool eos = false;
int read_index = 0;
int write_index = 0;
int N_block = 0;
int N_number = 0;
pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// generazione numeri casuali
void *genera(void *arg)
{
    while (N_number > 0)
    {
        pthread_mutex_lock(&producer_mutex);
        // sospensione nel caso di buffer pieno
        while (N_block >= BUFFER_SIZE)
        {
            pthread_cond_wait(&not_full, &producer_mutex);
        }
        // generazione nuovo numero casuale e inserimento nel buffer circolare
        ring_buffer[write_index] = rand();
        N_number--;
        // incremento circolare indice di scrittura blocchi dati
        write_index = (write_index + 1) % BUFFER_SIZE;
        // incremento contatore numero di blocchi dati
        N_block++;
        // notifica condizione buffer non vuoto al consumatore
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&producer_mutex);
    }
    eos = true;
    // notifica al consumatore eventualmente sospeso in attesa di dati
    pthread_cond_signal(&not_empty);
    return NULL;
}

// visualizzazione numeri casuali
void *visualizza(void *arg)
{
    while (!eos || N_block > 0)
    {
        pthread_mutex_lock(&consumer_mutex);
        if (N_block > 0)
        {
            // visualizzazione numero casuale prelevato dal buffer circolare
            printf("%d\n", ring_buffer[read_index]);
            // decremento circolare indice di lettura blocchi dati
            read_index = (read_index + 1) % BUFFER_SIZE;
            // decremento contatore numero di blocchi dati
            N_block--;
            // notifica condizione buffer non pieno al produttore
            pthread_cond_signal(&not_full);
        }
        else
        {
            // sospensione nel caso di buffer vuoto
            pthread_cond_wait(&not_empty, &consumer_mutex);
        }
        pthread_mutex_unlock(&consumer_mutex);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    // verifica degli argomenti della riga di comando
    if (argc != 2)
    {
        printf("Uso: %s numero-generazioni\n", argv[0]);
        return -1;
    }
    N_number = atoi(argv[1]);
    // inizializzazione variabili condivise
    N_block = 0;
    // esecuzione dei thread di lettura e scrittura
    pthread_t generazione_thread, visualizzazione_thread;
    pthread_create(&generazione_thread, NULL, genera, NULL);
    pthread_create(&visualizzazione_thread, NULL, visualizza, NULL);
    // attesa della conclusione dei thread e chiusura dei file
    pthread_join(generazione_thread, NULL);
    pthread_join(visualizzazione_thread, NULL);
    return 0;
}
