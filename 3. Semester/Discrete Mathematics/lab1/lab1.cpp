#include <iostream>
#include <cmath>
#include <memory>

using namespace std;

void metoda1(int a, int lambda1, int lambda2, int a_0, int a_1, int n) {
    int diskriminanta = pow(lambda1, 2) - 4*a*lambda2;
    unique_ptr<double[]> r(new double[2]);
       
    if (diskriminanta > 0) {
        r[0] = (-lambda1 + sqrt(diskriminanta)) / (2 * a);
        r[1] = (-lambda1 - sqrt(diskriminanta)) / (2 * a);
    } else {
        r[0] = -lambda1 / (2 * a);
        r[1] = r[0];
    }

    double x, y;
    int a_n;
    if (r[0] == r[1]) {
        x = a_0;
        y = (a_1 - x * r[0]) / r[1];
        a_n = x * pow(r[0], n) + y * n *  pow(r[1], n);
    } 
    else {
        x = (a_1 - (a_0 * r[1])) / (r[0] - r[1]);
        y = a_0 - x;
        a_n = x * pow(r[0], n) + y * pow(r[1], n);
    }

    cout << "Vrijednost n-tog clana niza pomocu formule: " << a_n << endl;

    return;
}

int metoda2(int lambda1, int lambda2, int a_0, int a_1, int n) {
    int a;
    if (n > 0) {
        // an+2 = l1*an+1 + l2*an --> an = l1*an-1 + l2*an-2
        a = a_1 * lambda1 + a_0 * lambda2;
        return metoda2(lambda1, lambda2, a_1, a, --n);
    }
    
    return a_0;
}

int main(void) {
    int lambda1, lambda2, a_0, a_1, n, a = 1;

    {
        cout << "Unesite prvi koeficijent λ_1 rekurzivne relacije: ";
        cin >> lambda1;

        cout << "Unesite drugi koeficijent λ_2 rekurzivne relacije: ";
        cin >> lambda2;

        cout << "Unesite vrijednost nultog clana niza a_0 :";
        cin >> a_0;

        cout << "Unesite vrijednost clana niza a_1: ";
        cin >> a_1;

        cout << "Unesite redni broj n trazenog clana niza: ";
        cin >> n;
    }

    metoda1(a, -lambda1, -lambda2, a_0, a_1, n);
    cout << "Vrijednost n-tog clana niza iz rekurzije: " <<  metoda2(lambda1, lambda2, a_0, a_1, n) << endl;

    return 0;
}