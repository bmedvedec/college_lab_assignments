#include <iostream>
#include <ctime>
using namespace std;

class Stog
{
 private:
    static const int MAX = 10;
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
    
    bool pop(int &element)
    {
        if (top < 0)
            return false;
        element = stog[top--];
        return true;
    }
};

int main(void)
{
    srand(time(NULL));
    Stog *stog = new Stog;
    
    int element;
    for (int i = 0; i < 10; i++)
    {
        element = rand() % 10 + 1;
        stog->push(element);
    }

    Stog *stog2 = new Stog;

    while (stog->pop(element))
        stog2->push(element);
    while (stog2->pop(element))
        cout << element << endl;

    delete stog;
    delete stog2;
    return 0;
}