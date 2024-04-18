#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
// struct classe (in quanto la classe è composta da numero e sezione)
typedef struct
{
    int numero;
    char sezione;
} class;
// struct studente
typedef struct
{
    char nome[20];
    char cognome[20];
    float media;
    class classe;
} studente;
// funzione che stampa i dati dello studente su file
void *scriviSuFile(void *stud)
{
    FILE *file = fopen("testoStudenteThreads.txt", "w");
    fprintf(file, "%s", "^^^^^^^^^^^^^^^^^^^^\n");
    fprintf(file, "Nome: %s\n", ((studente *)stud)->nome);
    fprintf(file, "Cognome: %s\n", ((studente *)stud)->cognome);
    fprintf(file, "Classe: %d%c\n", ((studente *)stud)->classe.numero, ((studente *)stud)->classe.sezione);
    fprintf(file, "Media: %.2f\n", ((studente *)stud)->media);
    fclose(file);
    printf("\n^^^^^^^^^^^^^^^^^^^^\n");
    printf("Scrittura su file terminata\n");
    return NULL;
} // funzione che stampa i dati di uno studente
void *stampa(void *stud)
{
    printf("\n^^^^^^^^^^^^^^^^^^^^\n");
    printf("Nome: %s\n", ((studente *)stud)->nome);
    printf("Cognome: %s\n", ((studente *)stud)->cognome);
    printf("Classe: %d%c\n", ((studente *)stud)->classe.numero, ((studente *)stud)->classe.sezione);
    printf("Media: %.2f\n", ((studente *)stud)->media);
    return NULL;
}
int main()
{
    pthread_t t1, t2;
    studente stud1;
    class classeStud1;

    printf("Inserire nome studente: ");
    scanf("%s", stud1.nome);
    printf("Inserire cognome studente: ");
    scanf("%s", stud1.cognome);
    printf("Inserire media studente: ");
    scanf("%f", &stud1.media);
    printf("Inserire numero della classe studente: ");
    scanf("%d", &classeStud1.numero);
    printf("Inserire sezione della classe studente:");
    scanf(" %c", &classeStud1.sezione);

    // assegno allo studente la classe    
    stud1.classe = classeStud1;
    pthread_create(&t1, NULL, &stampa, (void *)&stud1);
    pthread_create(&t2, NULL, &scriviSuFile, (void *)&stud1);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}