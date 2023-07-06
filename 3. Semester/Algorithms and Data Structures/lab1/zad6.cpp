#include <iostream>
#include <cstring>

using namespace std;

char *ostaviSlova(string ulaz) {
    int brojSlova = 0;
    
    for (char& c : ulaz) {
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') 
            brojSlova++;
    }

    char* niz = new char[brojSlova + 1];
    int i = 0;
    for (char& c : ulaz) {
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            niz[i] = c;
            i++;
        }
    }

    niz[i] = '\0';

    return niz;
}

int main(void) {
    string ulaz = "asp12_i_ASP13";
    char *niz = ostaviSlova(ulaz);
    for (int i = 0; i < strlen(niz); i++) {
        cout << niz[i];
    }


    delete[] niz;

    return 0;
}