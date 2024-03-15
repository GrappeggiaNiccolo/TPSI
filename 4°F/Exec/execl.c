#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    printf("Il mio pid è %d\n", getpid());
    // execl("./nuovoProcesso", "nuovoProcesso", NULL); // il processo termina ed esegue il nuovo processo, NULL indica che si vuole solo eseguire il secondo processo, altrimenti si possono passare dei parametri che andranno in argv
    execl("./nuovoProcesso", "nuovoProcesso", "Buongiorno", "Ora comando io", NULL); // execl = API
    // execl("/bin/ls", "ls", "-a", "-l", "-t", NULL);
    printf("Che ci fai qui?");

    // execv = si usa un array per passare i parametri invece che scriverli nella firma
}