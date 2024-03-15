#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{ // questo processo eredita il layout di memoria del primo e lo sostituisce
    printf("Sono il nuovo processo, il mio pid è %d\n", getpid());
    printf("Messaggio: %s\n", argv[1]);
    printf("Messaggio2: %s\n", argv[2]);
    // execl("./execl.sh", "execl.sh", NULL);
}