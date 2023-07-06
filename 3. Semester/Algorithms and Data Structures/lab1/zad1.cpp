#include <iostream>

using namespace std;

void ispis(float polje[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (polje[i] < 0) {
            cout << polje[i] << " ";
            break;
        }
    }
    if (i < n) {
        ispis(polje + (i + 1), n - (i + 1));
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

    float* A = new float[n];
    for (int i = 0; i < n; i++) {
        cout << "Upisite " << i + 1 << ". element polja: ";
        cin >> A[i];
    }

    ispis(A, n);

    delete[] A;

    return 0;
}