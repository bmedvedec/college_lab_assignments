#include <iostream>
#include <ctime>
using namespace std;

class Stog
{
 private:
    static const int MAX = 100;
    int stog[MAX];
    int top = -1;

 public:
    bool push(int element)
    {
        if (top >= MAX)
            return false;
        stog[++top] = element;
        return true;
    }

    void ispis()
    {
        for (int i = MAX - 1; i >= 0; i--)
        {
            cout << stog[i] << endl;
        }
        return;
    }
};

int main(void)
{
    srand(time(NULL));
    Stog *stog = new Stog;

    int element;
    for (int i = 0; i <= 100; i++)
    {
        element = rand();
        stog->push(element);
    }

/*
    cout << "Brojevi na stogu: " << endl;
    stog->ispis();
*/
    delete stog;
    return 0;
}