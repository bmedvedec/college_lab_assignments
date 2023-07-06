#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int zbrojiKvadrate(int polje[], int n) {
    if (n == 0) {
        return 0;
    }

    int root = sqrt(polje[n - 1]);
    if ((root * root) == polje[n - 1]) {
        return zbrojiKvadrate(polje, n - 1) + polje[n - 1];
    } 
    else {
        return zbrojiKvadrate(polje, n - 1);
    }
}

int main(void) {
    int n;
    do {
        cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
        cin >> n;
        if (n <= 0) {
            cout << "Velicina polja mora biti veca od nule!" << endl;
        }
    } while (n <= 0);

    int* A = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100 + 1; 
    }

    cout << "Ispis polja: [";
    for (int i = 0; i < n - 1; i++) {
        cout << A[i] << ", ";
    }
    cout << A[n - 1] << "]" << endl;

    cout << "Zbroj kvadrata: " << zbrojiKvadrate(A, n) << endl;

    delete[] A;

    return 0;
}