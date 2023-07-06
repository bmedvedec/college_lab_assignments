#include <iostream>
#include <cmath>

using namespace std;

void f(int polje[], int n, int m) {
    if (n == 0) {
        return;
    }

    polje[n - 1] = pow(m, n - 1);
    f(polje, n - 1, m);
}

int main(void) {
    int n, m;
    cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
    cin >> n;
    cout << "Upisi parametar: ";
    cin >> m;

    int* A = new int[n];

    f(A, n, m);

    cout << "Ispis polja: [";
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << A[i] << "]" << endl;
        }
        else {
            cout << A[i] << ", ";
        }
    }

    delete[] A;
    return 0;
}