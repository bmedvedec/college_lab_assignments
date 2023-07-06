#include <iostream>
using namespace std;

struct zapis
{
    int broj;
    string naziv;
};

bool operator<(const zapis &a, const zapis &b)
{
    return a.broj < b.broj;
}

bool operator>(const zapis &a, const zapis &b)
{
    return a.broj > b.broj;
}

void insertionSort(zapis A[], int n, char smjer)
{   
    int i, j;
    zapis temp;
    if (smjer == '0')
    { 
        for (i = 1; i < n; i++)
        {
            temp = A[i];
            for (j = i; j >= 1 && A[j - 1] > temp; j--)
            {
                A[j] = A[j - 1];
            }
            A[j] = temp;
        }
    }
    else
    {
        for (i = 1; i < n; i++)
        {
            temp = A[i];
            for (j = i; j >= 1 && A[j - 1] < temp; j--)
            {
                A[j] = A[j - 1];
            }
            A[j] = temp;
        }
    }
}

int main(void)
{
    int n, i;
    cout << "Upisite broj zapisa: ";
    cin >> n;

    zapis *A = new zapis[n];
    zapis temp;
    for (i = 0; i < n; i++)
    {
        cout << "Upisite postanski broj " << i + 1 << ". mjesta: ";
        cin >> temp.broj;
        cin.ignore(1, '\n');
        cout << "Upisite naziv " << i + 1 << ". mjesta: ";
        getline(cin, temp.naziv);
        A[i] = temp;
    }

    char smjer;
    cout << "Upisite smjer sortiranja: ";
    cin >> smjer;

    insertionSort(A, n, smjer);
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << ". mjesto : " << A[i].broj << " - " << A[i].naziv << endl;
    }

    delete[] A;
    return 0;
}