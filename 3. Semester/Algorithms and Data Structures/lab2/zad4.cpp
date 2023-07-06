#include <iostream>
#include <ctime>
using namespace std;

class Stog
{
    struct StogElement
    {
        int data;
        StogElement *next;
    };

    StogElement *top = nullptr;

 public:
    bool push(int element)
    {
        StogElement *newElement = new (nothrow) StogElement;
        if (newElement == nullptr)
            return false;
        newElement->data = element;
        newElement->next = top;
        top = newElement;
        return true;
    }

    void ispis()
    {
        StogElement **p;
        for (p = &top; *p; p = &((*p)->next))
        {
            cout << (*p)->data << endl;
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

    cout << "Brojevi na stogu: " << endl;
    stog->ispis();

    delete stog;
    return 0;
}