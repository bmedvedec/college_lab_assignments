#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

int* randomSquared(int polje[], int n) {
    int* arrayRandomSquared = new int[n];
    for (int i = 0; i < n; i++) {
        arrayRandomSquared[i] = pow(polje[i], 2);
    }

    int j, temp;
    for (int i = 0; i < n; i++) {
        j = rand() % n;
        swap(arrayRandomSquared[i], arrayRandomSquared[j]);
    }

    return arrayRandomSquared;
}

int main(void) {
    srand(time(NULL));

    int n;
    cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
    cin >> n;

    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "Upisi " << i + 1 << ". element polja: ";
        cin >> array[i];
    }

    int* arrayRandomSquared = randomSquared(array, n);
    cout << "Ispis polja: [";
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            cout << arrayRandomSquared[i] << "]" << endl;
        }
        else {
            cout << arrayRandomSquared[i] << ", ";
        }
    }

    delete[] array;
    delete[] arrayRandomSquared;

    return 0;
}