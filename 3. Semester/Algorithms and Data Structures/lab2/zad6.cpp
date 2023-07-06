#include <iostream>
using namespace std;

class Red
{
 private:
    static const int MAX = 10;
    double red[MAX];
    int ulaz = 0;
    int izlaz = 0;

 public:
    bool dodaj(double broj)
    {
        if (ulaz >= MAX)
            return false;
        red[ulaz++] = broj;
        return true;
    }

    bool skini(double *broj)
    {
        if (ulaz == izlaz)
            return false;
        *broj = red[izlaz++];
        return true;
    }
};

int main(void)
{
    int n;
    cout << "Upisi broj elemenata u redu: ";
    cin >> n;

    Red *red = new Red;
    
    double element;
    for (int i = 0; i < n; i++)
    {
        cout << "Upisite " << i + 1 << ". element: ";
        cin >> element;
        red->dodaj(element);
    }

    cout << "Obrisani elementi: " << endl;
    for (int i = 0; i < n; i++)
    {
        red->skini(&element);
        cout << i + 1 << ". " << element << endl;
    }

    delete red;
    return 0;
}