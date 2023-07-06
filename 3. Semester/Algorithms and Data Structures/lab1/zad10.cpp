#include <iostream>
#include <cmath>

using namespace std;

double f(double z, int k) {
    if (k < 0) {
        return 0;
    }
    
    if (k == 0) {
        return z;
    }

    return (-1 * pow(z, 2) * f(z, k - 1)) / (((2 * k) + 1) * (2 * k));
}

int main(void) {
    double z = 0.5;
    int k;
    while (true) {
        cout << "Upisi pozitivan cijeli broj k ili 100 000 za zaustavljanje programa: ";
        cin >> k;

        if (k == 100000) {
            break;
        }

        cout << "f(" << k << ") = " << f(z, k) << endl;
    }

    return 0;
}