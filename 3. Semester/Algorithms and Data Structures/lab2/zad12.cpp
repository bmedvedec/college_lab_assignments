#include <iostream>
using namespace std;

class Osoba
{
 private:
    string ime;
    unsigned short int starost;
    friend bool operator>(Osoba const &a, Osoba const &b);

 public:
    Osoba() {};
    Osoba(string ime, unsigned short int starost) : ime(ime), starost(starost) {};
    string getIme() { return ime; }
    unsigned short int getStarost() { return starost; }
    void setIme(string ime) { this->ime = ime; }
    void setStarost(unsigned short int starost) { this->starost = starost; }
    ~Osoba() {};
    Osoba &operator=(const Osoba &osoba)
    {
        this->ime = osoba.ime;
        this->starost = osoba.starost;

        return *this;
    }
};

bool operator>(Osoba const &a, Osoba const &b)
{
    if (a.starost == b.starost)
        return a.ime[0] > b.ime[0];
    return a.starost > b.starost;
}

template <typename T> void InsertionSort(T A[], int N)
{
    int i, j;
    T temp;
    for (i = 0; i < N; i++)
    {
        temp = A[i];
        for (j = i; j >= 1 && A[j - 1] > temp; j--)
        {
            A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}

int main(void)
{
    static const int MAX = 10;
    int i;
    Osoba *A = new Osoba[MAX];
    string ime;
    unsigned short int starost;

    for (i = 0; i < MAX; i++)
    {
        cout << "Upisi ime " << i + 1 << ". osobe: ";
        getline(cin, ime);
        cout << "Upisi starost " << i + 1 << ". osobe: ";
        cin >> starost;
        cin.ignore(1, '\n');
        A[i] = Osoba(ime, starost);
    }

    InsertionSort(A, MAX);

    cout << "Sortirano polje: {";
    for (i = 0; i < MAX; i++)
    {
        cout << "{\"" << A[i].getIme() << "\"," << A[i].getStarost() << "}";
        if (i == MAX - 1)
            cout << "}" << endl;
        else
            cout << ", ";
    }

    delete[] A;
    return 0;
}