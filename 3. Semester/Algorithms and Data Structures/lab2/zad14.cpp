#include <iostream>
using namespace std;

void Zamijeni(string *prvi, string *drugi)
{
    string temp = *prvi;
    *prvi = *drugi;
    *drugi = temp;
    return;
}

void BubbleSortPoboljsani(string A[], int N, int smjer)
{
    int i, j;
    bool swapHappened = true;
    if (smjer == 1)
    {
        for (i = 0; swapHappened; i++)
        {
            swapHappened = false;
            for (j = 0; j < N - 1 - i; j++)
            {
                if (A[j + 1] < A[j])
                {
                    Zamijeni(&A[j], &A[j + 1]);
                    swapHappened = true;
                }
            }
        }
    }
    else
    {
        for (i = 0; swapHappened; i++)
        {
            swapHappened = false;
            for (j = 0; j < N - 1 - i; j++)
            {
                if (A[j + 1] > A[j])
                {
                    Zamijeni(&A[j], &A[j + 1]);
                    swapHappened = true;
                }
            }
        }
    }
}

int main(void)
{
    static const int MAX = 4;
    string *A = new string[MAX];
    int i;

    for (i = 0; i < MAX; i++)
    {
        cout << "Upisite " << i + 1 << ". string: ";
        getline(cin, A[i]);
    }

    int smjer;
    cout << "Upisite smjer sortiranja: ";
    cin >> smjer;

    BubbleSortPoboljsani(A, MAX, smjer);

    cout << "Sortirano polje stringova: [";
    for (i = 0; i < MAX; i++)
    {
        cout << "\"" << A[i] << "\"";
        if (i == MAX - 1)
            cout << "}" << endl;
        else
            cout << ", ";
    }

    delete[] A;
    return 0;
}