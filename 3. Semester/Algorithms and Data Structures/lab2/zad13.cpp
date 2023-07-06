#include <iostream>
#include <algorithm>
using namespace std;

class Vozilo
{
 private:
    string model;
    int godina;
    friend bool operator<(Vozilo const &a, Vozilo const &b);

 public:
    Vozilo() {};
    Vozilo(string model, int godina) : model(model), godina(godina) {};
    string getModel() { return model; }
    int getGodina() { return godina; }
    void setModel(string model) { this->model = model; }
    void setGodina(int godina) { this->godina = godina; }
    ~Vozilo() {};
    Vozilo &operator=(Vozilo const &vozilo)
    {
        this->model = vozilo.model;
        this->godina = vozilo.godina;
        return *this;
    }
};

bool operator<(Vozilo const &a, Vozilo const &b)
{
    return (a.model == b.model) ? (a.godina > b.godina) : (a.model < b.model);
}

void Zamijeni(Vozilo &prvi, Vozilo &drugi)
{
    Vozilo temp = prvi;
    prvi = drugi;
    drugi = temp;
    return;
}

template <typename T> void SelectionSort(T A[], int N)
{
    int i, j, min;
    for (i = 0; i < N; i++)
    {
        min = i;
        for (j = i + 1; j < N; j++)
        {
            if (A[j] < A[min])
                min = j;
        }
        Zamijeni(A[i], A[min]);
    }
}

int main(void)
{
    static const int MAX = 10;
    Vozilo *A = new Vozilo[MAX];
    string model;
    int godina;
    int i;
    for (i = 0; i < MAX; i++)
    {
        cout << "Upisite model " << i + 1 << ". vozila: ";
        getline(cin, model);
        cout << "Upisite godinu proizvodnje " << i + 1 << ". vozila: ";
        cin >> godina;
        cin.ignore(1, '\n');

        A[i] = Vozilo(model, godina);
    }

    SelectionSort(A, MAX);

    cout << "Sortirana vozila: {";
    for (i = 0; i < MAX; i++)
    {
        cout << "{\"" << A[i].getModel() << "\"," << A[i].getGodina() << "}";
        if (i == MAX - 1)
            cout << "}" << endl;
        else
            cout << ", ";
    }

    delete[] A;
    return 0;
}