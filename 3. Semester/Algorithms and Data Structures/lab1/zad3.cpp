#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double pi(int n) {
    if (n == 1) {
        return 4;
    }
    else {
        return 4 * pow(-1, n + 1) * (1. / (2 * n - 1)) + pi(n - 1);
    }
}

int main(void) {
    int n;
    do {
        cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
        cin >> n;
        if (n < 0) {
            cout << "Velicina polja mora biti veca do nule!" << endl;
        }
    } while(n < 0);

    double* A = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = pi(i + 1);
    }

    cout << fixed;
    cout << setprecision(6);
    cout << "Ispis polja:" << endl;
    cout << "[";
    for (int i = 0; i < n - 1; i++) {
        cout << A[i] << ", ";
    }
    cout << A[n - 1] << "]";

    delete[] A;

    return 0;
}