#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

void vrtuljak();
void posjetitelj();
void brisi();

int id;
sem_t *slobodno = NULL;
sem_t *sjeo = NULL;
sem_t *ustani = NULL;
sem_t *prazan = NULL;
const int N = 4;

int main() 
{
    id = shmget(IPC_PRIVATE, sizeof(sem_t) * 4, 0600);
    if (id == -1)
        exit(1);

    slobodno = (sem_t *)shmat(id, NULL, 0);
    sjeo = slobodno + 1;
    ustani = slobodno + 2;
    prazan = slobodno + 3;

    sem_init(slobodno, 1, 0);
    sem_init(sjeo, 1, 0);
    sem_init(ustani, 1, 0);
    sem_init(prazan, 1, 0);

    struct sigaction act;
    act.sa_handler = brisi;
    sigaction(SIGINT, &act, NULL);

    if (fork() == 0) 
    {
        for (int i = 0; i < 2 * N; i++) 
        {
            if (fork() == 0) 
            {
                posjetitelj();
                exit(0);
            }
        }
        for (int i = 0; i < 2 * N; i++)
            wait(NULL);
    }

    vrtuljak();

    brisi();
    return 0;
}

void vrtuljak() {
    while (1) 
    {
        printf("\nVrtuljak je prazan! Otvaranje slobodnih mjesta...\n\n");
        for (int i = 0; i < N; i++)
            sem_post(slobodno);  // postavi n slobodnih mjesta

        for (int i = 0; i < N; i++) 
        {
            sem_wait(sjeo);  //čekaj da sjedne n posjetitelja
            printf("Sjeo posjetitelj %d\n", i + 1);
        }

        printf("\nVrtuljak se vrti...\n");
        sleep(2);
        printf("Vrtuljak se zaustavio, posjetitelji mogu sići\n\n");

        for (int i = 0; i < N; i++) 
        {
            sem_post(ustani);  // vrtnja je gotova, posjetitelji mogu ustat i izaći
            printf("Izašao posjetitelj %d\n", i + 1);
        }

        for (int i = 0; i < N; i++)
            sem_wait(prazan);  // pričekaj da svi izađu
    }
}

void posjetitelj() {
    while (1)
    {
        sem_wait(slobodno);  // uđi u vrtuljak
        sem_post(sjeo);      // sjedni
        sem_wait(ustani);    //čekaj da možeš ustat
        sem_post(prazan);    // izašao si i ostavio prazno mjesto za sobom
    }
}

void brisi() {
    sem_destroy(prazan);
    sem_destroy(ustani);
    sem_destroy(sjeo);
    sem_destroy(slobodno);
    shmdt(slobodno);
    shmctl(id, IPC_RMID, NULL);
    exit(0);
}