#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
using namespace std;

class Graph
{
    int vrhovi;         // broj vrhova
    list<int> *bridovi; // lista svih susjedstva
public:
    Graph(int vrhovi)
    {
        this->vrhovi = vrhovi;
        bridovi = new list<int>[vrhovi];
    }
    ~Graph() { delete[] bridovi; }

    void dodajBrid(int v1, int v2);
    void bojanjeGrafa();
};

// dodvanje bridova
void Graph::dodajBrid(int v1, int v2)
{
    bridovi[v1].push_back(v2);
    bridovi[v2].push_back(v1);
}

// odredivanje boja i kromatskog broja
void Graph::bojanjeGrafa()
{
    int boje[vrhovi]; // polje boja po vrhovima (-1 znaci neiskoristeno)
    boje[0] = 0;      // postavljanje boje prvog vrha
    for (int j = 1; j < vrhovi; j++)
        boje[j] = -1; // no color is assigned to j

    bool slobodno[vrhovi]; // privremeno polje slobodnih/zauzetih boja
    for (int j = 0; j < vrhovi; j++)
        slobodno[j] = false;

    // nadi boje za ostale vrhove
    for (int j = 1; j < vrhovi; j++)
    {
        // oznaci boje ostalih vrhova kao nedostupne
        list<int>::iterator i;
        for (i = bridovi[j].begin(); i != bridovi[j].end(); ++i)
            if (boje[*i] != -1)
                slobodno[boje[*i]] = true; // true = iskoristeno

        // nadi prvu sljedecu slobodnu boju
        int boja;
        for (boja = 0; boja < vrhovi; boja++)
            if (slobodno[boja] == false)
                break;

        boje[j] = boja; // dodaj prvu sljedecu slobodnu boju na popis

        // resetiraj za sljedecu iteraciju
        for (i = bridovi[j].begin(); i != bridovi[j].end(); ++i)
            if (boje[*i] != -1)
                slobodno[boje[*i]] = false;
    }

    // ispis
    int max = 0;
    for (int j = 0; j < vrhovi; j++)
    {
        // cout << "Vrh " << j + 1 << " --->  boja: " << boje[j] + 1 << endl;
        if (boje[j] + 1 > max)
            max = boje[j] + 1;
    }
    cout << "Kromatski broj zadanog grafa je " << max << endl;
}

int main(void)
{
    ifstream textFile;
    string textFileName;
    int n, s;

    cout << "Upisi naziv tekstualne datoteke: ";
    cin >> textFileName;
    textFile.open(textFileName);

    textFile >> n;
    // cout << "n: " << n << endl;

    textFile >> s;
    // cout << "s: " << s << endl;

    int poljeS[s];
    for (int i = 0; i < s; i++)
    {
        textFile >> poljeS[i];
        // cout << poljeS[i] << " ";
    }
    textFile.close();

    Graph graf(n);
    bool uPoljuS;
    // int matricaSusjedstva[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int it = 0; it < s; it++)
            {
                if (poljeS[it] == abs(i - j))
                {
                    uPoljuS = true;
                    break;
                }
                uPoljuS = false;
            }
            if (uPoljuS)
            {
                graf.dodajBrid(i, j);
                //    matricaSusjedstva[i][j] = 1;
            }
            /*
            else
            {
                matricaSusjedstva[i][j] = 0;
            }
            */
        }
    }
    cout << endl;
    graf.bojanjeGrafa();

    // ispis matrice susjedstva
    /*
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << matricaSusjedstva[i][j] << " ";
            cout << endl;
        }
    */
    return 0;
}