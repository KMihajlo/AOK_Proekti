#include <iostream>
#include <cstring>
using namespace std;
class PlDrustvo
{
private:
    char *ime;
    int brTuri;
    int brChlenovi;
public:
    PlDrustvo()
    {
        this->ime = new char[0];
        this->brChlenovi = 0;
        this->brTuri = 0;
    }
    PlDrustvo(char *ime, int brTuri, int brChlenovi)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->brTuri = brTuri;
        this->brChlenovi = brChlenovi;
    }
    ~PlDrustvo()
    {
        delete [] ime;
    }
    PlDrustvo(const PlDrustvo &p)
    {
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime, p.ime);
        this->brTuri = p.brTuri;
        this->brChlenovi = p.brChlenovi;
    }
    PlDrustvo & operator=(const PlDrustvo &p)
    {
        if(this!=&p)
        {
            delete [] ime;
            this->ime = new char[strlen(p.ime)+1];
            strcpy(this->ime, p.ime);
            this->brTuri = p.brTuri;
            this->brChlenovi = p.brChlenovi;
        }
        return *this;
    }
    PlDrustvo &operator+(const PlDrustvo &p)
    {
        PlDrustvo tmp;
        tmp.brChlenovi = this->brChlenovi + p.brChlenovi;
        if(brChlenovi > p.brChlenovi)
        {
            tmp.ime = new char[strlen(ime)+1];
            strcpy(tmp.ime, ime);
            tmp.brTuri = brTuri;
        }
        else
        {
            tmp.ime = new char[strlen(p.ime)+1];
            strcpy(tmp.ime, p.ime);
            tmp.brTuri = p.brTuri;
        }
        return tmp;
    }
    bool operator>(const PlDrustvo &p)
    {
        return this->brChlenovi > p.brChlenovi;
    }
    bool operator<(const PlDrustvo &p)
    {
        return this->brChlenovi < p.brChlenovi;
    }
    friend ostream &operator<<(ostream &out, const PlDrustvo &p)
    {
        out << "Ime: " << p.ime << " ";
        out << "Turi: " << p.brTuri << " ";
        out << "Clenovi: " << p.brChlenovi << endl;
        return out;
    }
    friend void najmnoguClenovi(PlDrustvo *p, int n);
};
void najmnoguClenovi(PlDrustvo *p, int n)
{
    int max = 0, k = 0;
    for(int i = 0; i < n; i++)
    {
        if(p[i].brChlenovi > max)
        {
            max = p[i].brChlenovi;
            k = i;
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << p[k] << endl;
}
int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++) {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;
    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
