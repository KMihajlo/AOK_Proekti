#include <iostream>
using namespace std;
class Krug
{
private:
    float r;
    const float PI = 3.14;
public:
    Krug(){}
    Krug(float r)
    {
        this->r = r;
    }
    float Ploshtina()
    {
        return PI*(r*r);
    }
    float Perimetar()
    {
        return 2 * PI * r;
    }
    int Proverka()
    {
        if(Ploshtina() == Perimetar())
            return 1;
        else
            return 0;
    }

};
int main()
{
    float r;
    cin >> r;
    Krug k(r);
    cout << k.Perimetar() << endl << k.Ploshtina() << endl << k.Proverka() << endl;
    return 0;
}
