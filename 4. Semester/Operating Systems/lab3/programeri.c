#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

void *programer(void *vrsta);
void udji(void *vrsta);
void izadji(void *vrsta);

const int brDretvi = 30;
int brojac[2] = {0,0};
int cekaju[2] = {0,0};
int pojeli[2] = {0,0};
int vrsta[2] = {0, 1};
const int N = 5;  //koliko programera iste vrste za redom moze uci u restoran

pthread_mutex_t monitor;
pthread_cond_t red[2];

int main() 
{
    srand(time(NULL));

    pthread_mutex_init(&monitor, NULL);
    pthread_cond_init(&red[0], NULL);
    pthread_cond_init(&red[1], NULL);
    
    pthread_t dretve[brDretvi];

    printf("Restoran otvoren!\n");

    for (int i = 0; i < brDretvi; i++)
    {
        int nasumicno = rand() % 2;
        if (nasumicno)
        {
            if (pthread_create(&dretve[i], NULL, programer, &vrsta[1]) != 0)
            {
                printf("Nije moguce stvoriti dretvu\n");
                    exit(1);
            }
        } else
        {
            if (pthread_create(&dretve[i], NULL, programer, &vrsta[0]) != 0)
            {
                printf("Nije moguce stvoriti dretvu\n");
                exit(1);
            }
        }
            
    }

    for (int i = 0; i < brDretvi; i++)
            pthread_join(dretve[i], NULL); 

    printf("Restoran zatvoren!\n");
    
    pthread_cond_destroy(&red[0]);
    pthread_cond_destroy(&red[1]);
    pthread_mutex_destroy(&monitor);
    return 0;
}

void *programer(void *vrsta)
{

    udji(vrsta);

    if (*((int *)vrsta) == 0)
        printf("%d. MS progamer jede\n", brojac[*((int *)vrsta)]);
    else
        printf("%d. Linux programer jede\n", brojac[*((int *)vrsta)]);
    sleep(2);
    
    izadji(vrsta);
}

void udji(void *vrsta)
{
    pthread_mutex_lock(&monitor);
    
    cekaju[*((int *)vrsta)]++;
    while (brojac[1 - *((int *)vrsta)] > 0 || 
    	((pojeli[*((int *)vrsta)] >= N) && (cekaju[1 - *((int *)vrsta)] > 0)))
    {
        pthread_cond_wait(&red[*((int *)vrsta)], &monitor);
    }
    
    if (*((int *)vrsta) == 0)
        printf("Usao MS programer\n");
    else 
        printf("Usao Linux programer\n");
    
    brojac[*((int *)vrsta)]++;
    cekaju[*((int *)vrsta)]--;
    pojeli[1 - *((int *)vrsta)] = 0;
    pojeli[*((int *)vrsta)]++;

    pthread_mutex_unlock(&monitor);
}

void izadji(void *vrsta)
{
    pthread_mutex_lock(&monitor);
    
    if (*((int *)vrsta) == 0)
        printf("Izasao MS programer\n");
    else 
        printf("Izasao Linux programer\n");
    
    brojac[*((int *)vrsta)]--;

    if (brojac[*((int *)vrsta)] == 0)
        pthread_cond_broadcast(&red[1 - *((int *)vrsta)]);
    
    pthread_mutex_unlock(&monitor);
}