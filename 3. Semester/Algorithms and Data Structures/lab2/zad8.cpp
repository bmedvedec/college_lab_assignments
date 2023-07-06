#include <iostream>
#include <ctime>
using namespace std;

class Red
{
    struct Cvor
    {
        int broj;
        Cvor *next;
    };

    Cvor *ulaz = nullptr;
    Cvor *izlaz = nullptr;

 public:
    bool dodaj(int broj)
    {
        Cvor *newElement = new (nothrow) Cvor;
        if (newElement == nullptr)
            return false;
        newElement->broj = broj;
        newElement->next = nullptr;
        if (ulaz == nullptr)
            izlaz = newElement;
        else
            ulaz->next = newElement;
        ulaz = newElement;
        return true;
    }

    bool poljeURed(int polje[], int n)
    {
        if (n == 0)
        {
            cout << "Svi elementi polja dodani u red." << endl;
            return true;
        }
        cout << "Dodaje se u red element: " << polje[n-1] << endl;
        if (!dodaj(polje[n - 1]))
        {
            cout << "Element nije uspjesno dodan u red!" << endl;
            return false;
        }
        return poljeURed(polje, n - 1);
    }
};

int main(void)
{
    srand(time(NULL));
    static const int MAX = 10;
    int *polje = new int[MAX];
    
    cout << "Clanovi polja: [";
    for (int i = 0; i < MAX; i++)
    {
        polje[i] = rand() % 10 + 1;
        if (i == MAX - 1)
            cout << polje[i] << "]" << endl;
        else
            cout << polje[i] << ", ";
    }

    Red *red = new Red;
    red->poljeURed(polje, MAX);

    delete[] polje;
    delete red;
    return 0;
}