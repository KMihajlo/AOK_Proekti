#include <iostream>
using namespace std;
class Agol
{
private:
    int stepeni;
    int minuti;
    int sekundi;
public:
    Agol(){}
    Agol(int stepeni, int minuti, int sekundi)
    {
        this->stepeni = stepeni;
        this->minuti = minuti;
        this->sekundi = sekundi;
    }
    void setStepeni(int stepeni)
    {
        this->stepeni = stepeni;
    }
    void setMinuti(int minuti)
    {
        this->minuti = minuti;
    }
    void setSekundi(int sekundi)
    {
        this->sekundi = sekundi;
    }
    int Convert()
    {
        return (stepeni * 3600) + (minuti * 60) + sekundi;
    }
};

int Proverka(int stepeni, int minuti, int sekundi)
{
    if(stepeni < 0 || stepeni > 360)
        return 1;
    else if(minuti < 0 || minuti > 59)
        return 1;
    else if(sekundi < 0 || sekundi > 59)
        return 1;
    else
        return 0;
}

int main()
{
    Agol a;
    int stepeni, minuti, sekundi;
    cin >> stepeni >> minuti >> sekundi;
    a.setStepeni(stepeni);
    a.setMinuti(minuti);
    a.setSekundi(sekundi);
    if(Proverka(stepeni, minuti, sekundi) == 1)
        cout << "Nevaliden vlez za agol" << endl;
    else
        cout << a.Convert() << endl;
    return 0;
}
