#include <iostream>
using namespace std;

struct zapis
{
    int sifra;
    string naziv;
};

bool operator<(zapis const &a, zapis const &b)
{
    return a.sifra < b.sifra;
}

bool operator>(zapis const &a, zapis const &b)
{
    return a.sifra > b.sifra;
}

void obicanBubbleSort(zapis A[], int n, char smjer)
{
    int i, j;
    if (smjer == '0')
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (A[j + 1] < A[j])
                    swap(A[j], A[j + 1]);
            }
        }
    }
    else
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (A[j + 1] > A[j])
                    swap(A[j], A[j + 1]);
            }
        }
    }
}

int main(void)
{
    int n, i;
    cout << "Upisite velicinu polja: ";
    cin >> n;

    zapis *A = new zapis[n];
    zapis element;

    for (i = 0; i < n; i++)
    {
        cout << "Upisi sifru " << i + 1 << ". zapisa: ";
        cin >> element.sifra;
        cin.ignore(1, '\n');
        cout << "Upisi naziv " << i + 1 << ". jela: ";
        getline(cin, element.naziv);

        A[i] = element;
    }

    char smjer;
    cout << "Upisite smjer sortiranja: ";
    cin >> smjer;

    obicanBubbleSort(A, n, smjer);

    for (i = 0; i < n; i++)
        cout << A[i].sifra << " - " << A[i].naziv << endl;

    delete[] A;
    return 0;    
}