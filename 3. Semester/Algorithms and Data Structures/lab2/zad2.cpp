#include <iostream>
#include <string>

using namespace std;

template <typename T> class Lista
{
    template <class X> struct Cvor
    {
        X data;
        Cvor<X> *next;
        Cvor<X> *prev;
    };

    Cvor<T> *head = nullptr;
    Cvor<T> *tail = nullptr;

 public:
    bool upis (T element)
    {
        Cvor<T> *newElement = new (nothrow) Cvor<T>;
        if (newElement == nullptr)
            return false;
        newElement->data = element;
        newElement->next = nullptr;
        newElement->prev = tail;

        if (tail == nullptr)
            head = newElement;
        else
            tail->next = newElement;

        tail = newElement;
        return true;
    }

    void ispis()
    {
        for (Cvor<T> *p = head; p; p = p->next)
        {
            cout << p->data << endl;
        }
        return;
    }
};

int main(void)
{
    int n;
    cout << "Upisi broj stringova: ";
    cin >> n;
    cin.ignore(1, '\n');
    Lista<string> *lista = new Lista<string>;

    string string;
    for (int i = 0; i < n; i++)
    {
        cout << "Upisite " << i + 1 << ". string: ";
        getline(cin, string);
        lista->upis(string);
    }

    cout << "Stringovi liste: " << endl;
    lista->ispis();

    delete lista;
    return 0;
}