#include <iostream>

using namespace std;

template <typename T> class Lista 
{
    template <class X> struct Cvor
    {
        X data;
        Cvor<X> *next;
    };

    Cvor<T> *head = nullptr;

 public:
    bool upis (T element) 
    {
        Cvor<T> *newElement = new (nothrow) Cvor<T>;
        if (newElement == nullptr)
             return false;
        newElement->data = element;
        newElement->next = nullptr;
        Cvor<T> **p;
        for (p = &head; *p; p = &((*p)->next))
            if (element < (*p)->data)
                break;
        newElement->next = *p;
        *p = newElement;
        return true;
    }

    void ispis()
    {
        for (Cvor<T> *p = head; p; p = p->next)
        {
            cout << p->data << " ";
        }
        cout << endl;
        return;
    }
};

int main(void)
{
    int n;
    cout << "Ucitaj broj elemenata: ";
    cin >> n;

    Lista<int> *lista = new Lista<int>;

    int element;
    for (int i = 0; i < n; i++)
    {
        cout << "Upisite " << i + 1 << ". element: ";
        cin >> element;
        lista->upis(element);
    }

    cout << "Elementi liste: ";
    lista->ispis();

    delete lista;
    return 0;
}