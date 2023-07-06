#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

void bridovi(int *matricaBridova, int n, int a, int b)
{
    int k, l;
    for (k = 0; k < n; k++)
    {
        for (l = 0; l < n; l++)
        {
            if (k == l)
            {
                *(matricaBridova + k * n + l) = -1;
            }
            else if (k > l)
            {
                *(matricaBridova + k * n + l) = pow((a * (l + 1) + b * (k + 1)), 2) + 1;
            }
            else
            {
                *(matricaBridova + k * n + l) = pow((a * (k + 1) + b * (l + 1)), 2) + 1;
            }
        }
    }
    return;
}

int pohlepniAlgoritam(int *matricaBridova, int n)
{
    int ciklus = 0, min1 = 0, min2, k, l, u, v, i = 0;  //u i v krajnji vrhovi
    int vrhovi[n + 1] = {0};

    for (k = 0; k < n; k++)
    {
        for (l = k + 1; l < n; l++)
        {
            if (k != l)
            {
                if (min1 == 0)
                {
                    min1 = *(matricaBridova + k * n + l);
                    u = k;
                    v = l;
                }
                else
                {
                    if (*(matricaBridova + k * n + l) < min1)
                    {
                        min1 = *(matricaBridova + k * n + l);
                        u = k;
                        v = l;
                    }
                }
            }
        }
    }

    ciklus += min1;
    vrhovi[i++] = u + 1;
    vrhovi[i++] = v + 1;
    bool prosao;
    int u1, v1;
    
    while (i < n)
    {
        min1 = 0;
        for (k = 0; k < n; k++)
        {
            prosao = false;
            if (k != u)
            {
                for (l = 0; l < (sizeof(vrhovi) / sizeof(*vrhovi)); l++)
                {
                    if (k == (vrhovi[l] - 1))
                    {
                        prosao = true;
                        break;
                    }

                }
                if (!prosao)
                {
                    if (min1 == 0)
                    {
                        min1 = *(matricaBridova + u * n + k);
                        u1 = k;
                    }
                    else
                    {
                        if (*(matricaBridova + u * n + k) < min1)
                        {
                            min1 = *(matricaBridova + u * n + k);
                            u1 = k;
                        }
                    }
                }
            }
        }

        min2 = 0;
        for (k = 0; k < n; k++)
        {
            prosao = false;
            if (k != v)
            {
                for (l = 0; l < (sizeof(vrhovi) / sizeof(*vrhovi)); l++)
                {
                    if (k == (vrhovi[l] - 1))
                    {
                        prosao = true;
                        break;
                    }
                }
                if (!prosao)
                {
                    if (min2 == 0)
                    {
                        min2 = *(matricaBridova + v * n + k);
                        v1 = k;
                    }
                    else
                    {
                        if (*(matricaBridova + v * n + k) < min2)
                        {
                            min2 = *(matricaBridova + v * n + k);
                            v1 = k;
                        }
                    }
                }
            }
        }

        if (min2 < min1)
        {
            ciklus += min2;
            vrhovi[i] = v1 + 1;
            v = v1;
        }
        else
        {
            ciklus += min1;
            vrhovi[i] = u1 + 1;
            u = u1;
        }

        i++;
        if (i == n)
        {
            ciklus += *(matricaBridova + u * n + v);
            vrhovi[i] = vrhovi[0];
        }
    }

/*  ispisi ciklus po vrhovima
    for (int i = 0; i < (sizeof(vrhovi) / sizeof(*vrhovi)); i++)
    {
        cout << vrhovi[i];
        if (i != (sizeof(vrhovi) / sizeof(*vrhovi)) - 1)
        {
            cout << "->";
        }
    }
    cout << endl;
*/

    return ciklus;
}

int iscrpniAlgoritam(int *matricaBridova, int n)
{
    int ciklus = 0;
    int vrhovi[n+1];

    for (int i = 0; i <= n; i++)
    {
        if (i == n)
        {
            vrhovi[i] = 1;
        }
        else
        {
            vrhovi[i] = i + 1;
        }
    }

    int min, j, i;
    int ciklusNiz[n+1];

    do 
    {
        min = 0;
        for (j = 0; j < (n - 1); j++)
        {
            min += *(matricaBridova + (vrhovi[j] - 1) * n + (vrhovi[j + 1] - 1));
        }

        min += *(matricaBridova + (vrhovi[0] - 1) * n + (vrhovi[n - 1] - 1));

        if (ciklus == 0)
        {
            ciklus = min;
            for (i = 0; i <= n; i++)
            {
                ciklusNiz[i] = vrhovi[i];
            }
        }
        else if (min < ciklus)
        {
            ciklus = min;
            for (i = 0; i <= n; i++)
            {
                ciklusNiz[i] = vrhovi[i];
            }

        }
    } while (next_permutation(vrhovi + 1, vrhovi + n));

/* ciklus po vrhovima
    for (i = 0; i <= n; i++)
    {
        cout << ciklusNiz[i] << " ";
    }
    cout << endl;
*/

    return ciklus;
}

int main(void)
{
    int n, a, b;
    cout << "Unesite redom, odvojene razmakom, parametre n, a i b: ";
    cin >> n >> a >> b;
    cout << endl;

    int matricaBridova[n][n];
    bridovi(&matricaBridova[0][0], n, a, b);

// matrica tezine bridova
    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            cout << matricaBridova[k][l] << " ";
        }
        cout << endl;
    }
    cout << endl;


    int ciklusPohlepni = 0;
    ciklusPohlepni = pohlepniAlgoritam(&matricaBridova[0][0], n);

    int ciklusIscrpni = 0;
    ciklusIscrpni = iscrpniAlgoritam(&matricaBridova[0][0], n);
    
    cout << "Pohlepni algoritam nalazi ciklus duljine " << ciklusPohlepni << endl;
    cout << "Iscrpni algoritam nalazi ciklus duljine " << ciklusIscrpni << endl;
    cout << "Pohlepni algoritam na ovom grafu " << ((ciklusPohlepni != ciklusIscrpni) ? "ne " : "") << "daje optimalno rjesenje!" << endl;

    return 0;
}