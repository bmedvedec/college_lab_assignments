#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <signal.h>

int id; //id segmenta kojeg ce koristiti procesi
int broj; //zajednicka varijabla za dretve unutar istog procesa
int *broj2; //zajednicka varijabla za dretve iz 2 procesa

void *entry_thread_job();
void work_thread_job();
void exit_thread_job();
void brisi(int sig);

int input_broj;
FILE *ispis_dat;

int main(int argc, char* argv[])
{
    input_broj = atoi(argv[1]);
    printf("Pokrenuta RADNA DRETVA\n");

    id = shmget(IPC_PRIVATE, sizeof(int), 0600); //zauzimanje zajednicke memorije    

    if (id == -1)
        exit(1); //greska, nema zajednicke memorije

    broj2 = (int *) shmat(id, NULL, 0); //vezanje segmenta na adresni prostor procesa
    *broj2 = 0;
    broj = 0;

    struct sigaction act;   //u slucaju prekida brisi memoriju
    act.sa_handler = brisi;
    sigaction(SIGINT, &act, NULL);

    int i;
    pthread_t entry_thread;

    fclose(fopen("ispis.txt", "w"));
    ispis_dat = fopen("ispis.txt", "a+");

    if (fork() == 0)
    {
        printf("Pokrenut IZLAZNI PROCES\n");
        exit_thread_job();
        exit(0);
    }

    if (pthread_create(&entry_thread, NULL, entry_thread_job, NULL) != 0)
    {
        printf("Nije moguce stvoriti novu dretvu!\n");
        exit(1);
    }

    work_thread_job();
    pthread_join(entry_thread, NULL);
    wait(NULL);
    brisi(0);
    
    return 0;
}

void *entry_thread_job()
{
    printf("Pokrenuta ULAZNA DRETVA\n");
    srand(time(NULL));
    sleep(1);

    for (int i = 0; i < input_broj; i++)
    {
        while (broj != 0);
        broj = rand() % 100 + 1;
        if (i == 0) printf("\n");
        printf("ULAZNA DRETVA: broj %d\n", broj);
        sleep(rand() % 5 + 1);
    }
    printf("Zavrsila ULAZNA DRETVA\n");
}

void work_thread_job()
{
    for (int i = 0 ; i < input_broj; i++)
    {
        while (broj == 0);
        printf("RADNA DRETVA: procitan broj %d i povecan na %d\n", broj, broj+1);
        broj++;
        *broj2 = broj;
        broj = 0;
    }
    sleep(1);
    printf("Zavrsila RADNA DRETVA\n");
}

void exit_thread_job()
{
    for (int i = 0; i < input_broj; i++)
    {
        while (*broj2 == 0);
        fprintf(ispis_dat, "%d\n", *broj2);
        printf("IZLAZNI PROCES: broj upisan u datoteku %d\n\n", *broj2);
        *broj2 = 0;
    }
    printf("Zavrsio IZLAZNI PROCES\n");
}

void brisi(int sig)
{
    //oslobadanje zajednicke memorije
    (void) shmdt((char *) broj2);
    (void) shmctl(id, IPC_RMID, NULL);
    if (sig != 0) printf("Doslo je do prekida u radu programa!");
    exit(0);
}