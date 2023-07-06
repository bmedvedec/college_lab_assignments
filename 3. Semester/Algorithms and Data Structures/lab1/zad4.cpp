#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

double exp(double x, int n, int *fakt, double *xpot) {
    if (n < 0) {
        return 0;
    }
    return (*xpot) / (*fakt) + exp(x, n - 1, fakt + 1, xpot + 1);
}

int main(void) {
    int n;
    double x;
    
    do {
        cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
        cin >> n;
    } while (n <= 0);

    cout << "Upisi vrijednost broja x: ";
    cin >> x;

    int* nFact = new int[n];
    for (int i = 0; i < n; i++) {
        nFact[i] = factorial(i);
    }

    {
        std::cout << "Ispis faktorijela:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < n - 1; i++)
        {
            std::cout << nFact[i] << ", ";
        }
        std::cout << nFact[n - 1] << "]" << std::endl;
    }


    double* xPot = new double[n];
    for (int i = 0; i < n; i++) {
        xPot[i] = pow(x, i);
    }

    {
        std::cout << "Ispis potencija:" << std::endl;
        std::cout << "[";
        for (int i = 0; i < n - 1; i++)
        {
            std::cout << xPot[i] << ", ";
        }
        std::cout << xPot[n - 1] << "]" << std::endl;
    }

    
    double* A = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = exp(x, i, nFact, xPot);
    }

    cout << fixed;
    cout << setprecision(6);
    cout << "Ispis polja: [";
    for (int i = 0; i < n - 1; i++) {
        cout << A[i] << ", ";
    }
    cout << A[n - 1] << "]" << endl;

    delete[] nFact;
    delete[] xPot;
    delete[] A;
    

    return 0;
}