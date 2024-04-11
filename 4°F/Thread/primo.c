#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>

// Thread POSIX

void *stampaGiorno(void *par) // il puntatore a void non punta a niente, ma può essere indirizzato a qualunque tipo
{
    printf("Buongiornp\n");

    return 0;
}
void *stampaSera(void *par)
{
    printf("Buonsera\n");

    return 0;
}
void *stampaNotte(void *par)
{
    printf("Buonnotte\n");

    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t threadGiorno, threadSera, threadNotte;

    printf("cioa\n");
    // creo i thread
    pthread_create(&threadGiorno, NULL, &stampaGiorno, NULL);
    pthread_create(&threadSera, NULL, &stampaSera, NULL);
    pthread_create(&threadNotte, NULL, &stampaNotte, NULL);

    printf("\n");
    // aspetto che i thread finiscano l'esecuzione
    pthread_join(threadGiorno, NULL);
    pthread_join(threadSera, NULL);
    pthread_join(threadNotte, NULL);
    // return 0; // bisogna aspettare che i thread finiscano
    
    // gcc primo.c -o primo.sh -l pthread
}