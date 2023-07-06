#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
    srand(time(NULL));

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int disk[n][16];
    int okvir[m];
    int tablica[n][16];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            tablica[i][j] = 0;
            disk[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++)
        okvir[i] = 0;

    int t = 0;
    int i, zapis_tab, sadrzaj_disk, stranica, p, sadrzaj_adrese, t_min;
    int proces, str, frame;

    while (1)
    {
        for (i = 0; i < n; i++)
        {
            printf("---------------------------\n");
            printf("proces: %d\n", i);
            printf("\tt: %d\n", t);
            int j, adresa;
            unsigned short x = (rand() % USHRT_MAX) & 0x3FE;    //generirana log adresa
            printf("\tlog. adresa: 0x%04x\n", x);
            stranica = (x >> 6) & 0b0000000000001111;   //broj stranice
            zapis_tab = tablica[i][stranica];   //zapis tablice stranicenja
            p = (zapis_tab >> 5) & 0b0000000000000001;   //bit p
            t_min = t;

            if (!p)     //adresa x nije prisutna ako je p=0
            {
                printf("\tPromasaj!\n");
                for (j = 0; j < m; j++)
                {
                    if (okvir[j] == 0)
                        break;
                }

                if (j != m)     //ima prazan okvir
                {
                    sadrzaj_disk = disk[i][stranica];
                    okvir[j] = sadrzaj_disk;
                    printf("\t\tdodijeljen okvir: 0x%04x\n", j);
                } 
                else        //nema praznog okvira
                {
                    for (int k = 0; k < n; k++)
                    {
                        for (int l = 0; l < 16; l++)
                        {
                            if ((tablica[k][l] & 0b0000000000011111) < t_min && ((tablica[k][l] & 0b0000000000100000) >> 5) == 1)
                            {
                                t_min = tablica[k][l] & 0b0000000000011111;     //aktivna stranica sa najmanjim LRU poljem
                                proces = k;
                                str = l;
                                frame = (tablica[k][l] & 0b1111111111000000) >> 6;
                            }
                        }
                    }

                    printf("\t\tIzbacujem stranicu 0x%04x (%d) iz procesa %d\n", (str << 6), str, proces);
                    printf("\t\tlru izbacene stranice: 0x%04x\n", (tablica[proces][str] & 0b0000000000011111));
                    disk[proces][str] += okvir[frame];
                    okvir[frame] = disk[i][stranica];
                    tablica[proces][str] = tablica[proces][str] & 0b1111111111000000;
                    printf("\t\tdodijeljen okvir: 0x%04x\n", frame);                                
                    j = frame;
                }
            }

            p = 1;
            tablica[i][stranica] = ((j & 0b1111111111) << 6) | ( (p & 0b1) << 5) | (t & 0b11111);       //azuriraj tablicu stranicenja
            adresa = ((j & 0b1111111111) << 6) | (x & 0b111111);
            printf("\tfiz.adresa: 0x%04x\n", adresa);
            zapis_tab = tablica[i][stranica] & 0b0000000000111111;
            printf("\tzapis tablice: 0x%04x\n", zapis_tab);
            printf("\tsadrzaj adrese: %d\n", okvir[j]);
            okvir[j]++;     //povecaj "brojac"
            sleep(1);

            if (t == 31)
            {
                t = 0;
                for (int k = 0; k < n; k++)
                {
                    for (int l = 0; l < 16; l++)
                        tablica[k][l] = tablica[k][l] & 0b1111111111100000;
                }
                
                tablica[i][stranica] = tablica[i][stranica] & 0b1111111111100001;
            }
            else    
                t++;
        }
    }

    return 0;
}