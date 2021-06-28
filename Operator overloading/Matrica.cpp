#include <iostream>
#include <cstring>
using namespace std;
class Matrica
{
private:
    float a[10][10];
    int brojElementi;
public:
    Matrica()
    {
        this->brojElementi = 10;
        for(int i = 0; i < brojElementi; i++)
        {
            for(int j = 0; j < brojElementi; j++)
            {
                this->a[i][j] = 0;
            }
        }
    }
    Matrica(int brojElementi, float *a[])
    {
        this->brojElementi = brojElementi;
        for(int i = 0; i < brojElementi; i++)
        {
            for(int j = 0; j < brojElementi; j++)
            {
                this->a[i][j] = a[i][j];
            }
        }
    }
    Matrica &operator+(int n)
    {
        for(int i = 0; i < brojElementi; i++)
        {
            for(int j = 0; j < brojElementi; j++)
            {
                this->a[i][j] += n;
            }
        }
        return *this;
    }
    Matrica &operator-(const Matrica &m)
    {
        for(int i = 0; i < brojElementi; i++)
        {
            for(int j = 0; j < brojElementi; j++)
            {
                this->a[i][j] -= m.a[i][j];
            }
        }
        return *this;
    }
    Matrica &operator*(const Matrica &m)
    {
        Matrica tmp;
        for(int i = 0; i < brojElementi; i++)
        {
            for(int j = 0; j < brojElementi; j++)
            {
                for(int k = 0; k < brojElementi; k++)
                {
                    tmp.a[i][j] += this->a[i][k] * m.a[k][j];
                }
            }
        }
        return tmp;
    }
    friend ostream &operator <<(ostream &out, const Matrica &m)
    {
        for(int i = 0; i < m.brojElementi; i++)
        {
            for(int j = 0; j < m.brojElementi; j++)
            {
                out << m.a[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
    friend istream &operator>>(istream &in, Matrica &m)
    {
        in >> m.brojElementi >> m.brojElementi;
        for(int i = 0; i < m.brojElementi; i++)
        {
            for(int j = 0; j < m.brojElementi; j++)
            {
                in >> m.a[i][j];
            }
        }
        return in;
    }
};
int main()
{
    Matrica A, B, C;
    cin >> A >> B >> C;
    Matrica D = B * C;
    Matrica R = A - D + 2;
    cout << R;
}
