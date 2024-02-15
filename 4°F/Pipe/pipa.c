#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int global1 = 130;
int global2;

int main()
{
    printf("Prova, \nlezione sul layout di memoria in LInux\n");

    //    size a.out
    //    text    data     bss     dec     hex filename
    //    1420     604      12    2036     7f4 a.out
    //    objdump -s a.out
    //    objdump -s -j .data a.out
    int a;
    while (1)
    {
        printf("%d\n", getpid());
        printf("%p\n", &a);
        sleep(1);
    }
    // l'indirizzo di memoria sta tra il minimo e il massimo dello stack
    
    return 0;
}