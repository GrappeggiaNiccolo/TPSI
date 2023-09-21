#include <stdio.h>
int main(int argc, char *argv[])
{
    printf("Parametri: %d\n\n", argc - 1);

    for (int i = 0; i < argc; i++)
    {
        printf("Paramentri: %s\n", argv[i + 1]);
    }

    return 0;
}