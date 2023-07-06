#include <iostream>

using namespace std;

template <typename T> int binarnoTrazi(T polje[], int n, T x) {
    int left = 0;
    int right = n - 1;
    int index = -1;
    bool found = false;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (polje[middle] < x) {
            left = middle + 1;
        }
        else if (polje[middle] > x) {
            right = middle - 1;
        }
        else {
            found = true;
            index = middle;
            break;
        }
    }
    return index;
}

int main(void) {
    int n;
    cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
    cin >> n;

    float x;
    cout << "Upisi trazeni realni broj: ";
    cin >> x;

    float* A = new float[n];
    cout << "Clanovi polja: [";
    for (int i = 0; i < n; i++) {
        A[i] = i * 1.1;
        if (i == (n - 1)) {
            cout << A[i] << "]" << endl; 
        }
        else {
            cout << A[i] << ", ";
        }
    }

    int index = binarnoTrazi(A, n, x);
    if (index != -1) {
        cout << "Broj " << x << " se nalazi u polju na mjestu " << index << endl;
    } 
    else {
        cout << "Broj " << x << " se ne nalazi u polju" << endl;
    }



    int n2, x2;
    cout << "Upisi broj elemenata jednodimenzionalnog polja: ";
    cin >> n2;

    cout << "Upisi trazeni cijeli broj: ";
    cin >> x2;

    int* A2 = new int[n];
    cout << "Clanovi polja: [";
    for (int i = 0; i < n; i++) {
        A2[i] = i + 3;
        if (i == (n - 1)) {
            cout << A2[i] << "]" << endl; 
        }
        else {
            cout << A2[i] << ", ";
        }
    }

    int index2 = binarnoTrazi(A2, n2, x2);
    if (index2 != -1) {
        cout << "Broj " << x2 << " se nalazi u polju na mjestu " << index2 << endl;
    } 
    else {
        cout << "Broj " << x2 << " se ne nalazi u polju" << endl;
    }


    delete[] A;

    return 0;
}