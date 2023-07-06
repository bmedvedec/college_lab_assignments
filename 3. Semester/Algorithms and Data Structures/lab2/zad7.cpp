#include <iostream>
using namespace std;

class Red
{
    struct Cvor
    {
        double broj;
        Cvor *next;
    };

    Cvor *ulaz = nullptr;
    Cvor *izlaz = nullptr;

 public:
    bool dodaj(double broj)
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

    bool skini(double *broj)
    {
        if (izlaz == nullptr)
            return false;
        *broj = izlaz->broj;
        Cvor *temp = izlaz;
        izlaz = izlaz->next;
        if (izlaz == nullptr)
            ulaz = nullptr;
        delete temp;
        return true;
    }
};

int main(void)
{
    int n, i;
    cout << "Upisite broj elemenata: ";
    cin >> n;

    Red *red = new Red;

    double element;
    for (i = 0; i < n; i++)
    {
        cout << "Upisite " << i + 1 << ". element: ";
        cin >>  element;
        red->dodaj(element);
    }

    cout << "Skinuti elementi: " << endl;
    i = 0;
    while (red->skini(&element))
    {
        cout << i + 1 << ". element: " <<  element << endl;
        i++;
    }

    delete red;
    return 0;
}