#include <iostream>
#include <cstring>

using namespace std;

class SanitizedString {
 private:
    string str;

 public:
    SanitizedString(string string) {
        str = string;
        removeDuplicateWhitespace();
        removeNonAlphaChars();
    }

    void removeDuplicateWhitespace() {
        for (int i = 1; i < str.size(); i++) {
            if (str[i] == ' ' && str[i - 1] == ' ') {
                str.erase(str.begin() + i);
                i--;
            }
        }
    }

    void removeNonAlphaChars() {
        for (int i = 0; i < str.size(); i++) {
            if (!(isalpha(str[i]) || str[i] == ' ')) {
                str.erase(str.begin() + i);
                i--;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const SanitizedString& string);
};

ostream& operator<<(ostream& os, const SanitizedString& string) {
    os << string.str;
    return os;
}

int main(void) {
    string str;
    cout << "Ucitaj niz: ";
    getline(cin, str);

    SanitizedString sanString(str);

    cout << "Pocetni niz: " << str << endl;
    cout << "Sanitizirani niz: ";
    cout << sanString << endl;

    return 0;
}