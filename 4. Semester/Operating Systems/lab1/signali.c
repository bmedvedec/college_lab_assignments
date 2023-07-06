#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void obradi_dogadjaj(int sig);
void obradi_sigterm(int sig);
void obradi_sigint(int sig);
int obrada(int x);

int nije_kraj = 1;
int broj;
FILE *status_dat, *obrada_dat;

int main()
{
	struct sigaction act;
	
	//maskiranje signala SIGUSR1
	act.sa_handler = obradi_dogadjaj; //kojom se funkcijom signal obraduje
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGTERM); //blokirati i SIGTERM za vrijeme obrade
	act.sa_flags = 0; //naprednije mogucnosti preskocene
	sigaction(SIGUSR1, &act, NULL); //maskiranje signala preko sucelja OS-a

	//maskiranje signala SIGTERM
	act.sa_handler = obradi_sigterm;
	sigemptyset(&act.sa_mask);
	sigaction(SIGTERM, &act, NULL);
	
	//maskiranje signala SIGINT
	act.sa_handler = obradi_sigint;
	sigaction(SIGINT, &act, NULL);
	
	printf("Program s PID=%ld krenuo s radom\n", (long)getpid()); 
	//posao koji program radi:
	int x;
	
	status_dat = fopen("status.txt", "r+"); //otvaranje datoteke status.txt
	obrada_dat = fopen("obrada.txt", "r+"); //otvaranje datoteke obrada.txt
		
	broj = fscanf(status_dat, "%d", &broj); //procitaj broj iz status.txt
	
	if(broj == 0)
	{
		while(!feof(obrada_dat)) //citaj iz obrada.txt dok ne dodes do kraj datoteke
		{
			broj = fscanf(obrada_dat, "%d", &broj);
		}
	}
		
	fclose(status_dat); //zatvori status.txt datoteku
	status_dat = fopen("status.txt", "w+"); //otvori datoteku, ali prebrisi cijeli sadrzaj
	fprintf(status_dat, "%d", 0); //upisi 0 na pocetak datoteke
	
	while(nije_kraj)
	{
		broj++;
		x = obrada(broj);
		fscanf(obrada_dat, "%d", &x);
		sleep(5);
	}
	
	fclose(status_dat);
	status_dat = fopen("status.txt", "w+");
	fprintf(status_dat, "%d", broj);
	fclose(status_dat);
	fclose(obrada_dat);
	printf("Program s PID=%ld zavrsio s radom\n", (long)getpid());
	return 0;	
}

int obrada(int x)
{
	return x*x;
}

void obradi_dogadjaj(int sig)
{
	int i;
	printf("Pocetak obrade signala %d\n", sig);
	printf("%d\n", broj);
	for(int i = 0; i < 5; i++) sleep(1);
	printf("Kraj obrade signala %d\n", sig);
}

void obradi_sigterm(int sig)
{
	printf("Primio signal SIGTERM, spremam broj u status.txt prije izlaska iz programa\n");
	nije_kraj = 0;
}

void obradi_sigint(int sig)
{
	printf("Primio signal SIGINT, prekidam rad\n");
	exit(1);
}
