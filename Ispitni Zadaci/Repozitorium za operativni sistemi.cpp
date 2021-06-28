#include <iostream>
#include <cstring>
using namespace std;
enum Tip {
    LINUX, UNIX, WINDOWS
};
class OperativenSistem {
private:
    char *ime;
    float verzija;
    Tip t;
    float golemina;
public:
    OperativenSistem() {
        this->ime = NULL;
    }
    OperativenSistem(char *ime, float verzija, Tip t, float golemina) {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->verzija = verzija;
        this->t = t;
        this->golemina = golemina;
    }
    OperativenSistem(const OperativenSistem &o) {
        this->ime = new char[strlen(o.ime)+1];
        strcpy(this->ime, o.ime);
        this->verzija = o.verzija;
        this->t = o.t;
        this->golemina = o.golemina;
    }
    ~OperativenSistem() {
        delete [] ime;
    }
    void pecati() {
        cout << "Ime: " << ime << " Verzija: " << verzija << " Tip: " << t << " Golemina:" << golemina << "GB" << endl;
    }
    OperativenSistem & operator=(const OperativenSistem &o) {
        if(this != &o) {
            delete [] ime;
            this->ime = new char[strlen(o.ime)+1];
            strcpy(this->ime, o.ime);
            this->verzija = o.verzija;
            this->t = o.t;
            this->golemina = o.golemina;
        }
        return *this;
    }
    bool ednakviSe(const OperativenSistem &os) {
        if(strcmp(this->ime, os.ime)==0) {
            if(this->verzija == os.verzija) {
                if(this->t == os.t) {
                    if(this->golemina == os.golemina) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os) {
        if(this->verzija == os.verzija)
            return 0;
        if(this->verzija < os.verzija)
            return -1;
        if(this->verzija > os.verzija)
            return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba) {
        if(strcmp(this->ime, sporedba.ime) == 0&&this->t == sporedba.t)
            return true;
        else
            return false;
    }
};
class Repozitorium {
private:
    char ime[20];
    OperativenSistem *sistemi;
    int brojSistemi;
public:
    Repozitorium() {
        this->sistemi = NULL;
    }
    Repozitorium(char *ime) {
        strcpy(this->ime, ime);
        this->sistemi = new OperativenSistem[0];
        this->brojSistemi = 0;
    }
    ~Repozitorium() {
        delete [] sistemi;
    }
    Repozitorium(const Repozitorium &r) {
        strcpy(this->ime, r.ime);
        for(int i = 0; i < this->brojSistemi; i++) {
            this->sistemi[i] = r.sistemi[i];
        }
        this->brojSistemi = r.brojSistemi;
    }
    Repozitorium & operator=(const Repozitorium &r) {
        if(this!=&r) {
            delete [] sistemi;
            strcpy(this->ime, r.ime);
            this->brojSistemi = r.brojSistemi;
            this->sistemi = new OperativenSistem[brojSistemi];
            for(int i = 0; i < brojSistemi; i++) {
                this->sistemi[i] = r.sistemi[i];
            }
        }
        return *this;
    }
    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << ime << endl;
        for(int i = 0; i < brojSistemi; i++) {
            sistemi[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem) {
        int j = 0;
        for(int i = 0; i < brojSistemi; i++) {
            if(this->sistemi[i].ednakviSe(operativenSistem) == true) {
                continue;
            } else {
                this->sistemi[j] = sistemi[i];
                j++;
            }
        }
        brojSistemi = j;
    }
    void dodadi(const OperativenSistem &nov) {
        int j = 0, p = 0;
        for(int i = 0; i < brojSistemi; i++) {
            if(sistemi[i].istaFamilija(nov) == true) {
                if(sistemi[i].sporediVerzija(nov) == -1)
                {
                    p++;
                	sistemi[i] = nov;
                    break;
                }
            }
        }
        if(p == 0) {
            OperativenSistem *os = new OperativenSistem[brojSistemi+1];
            for(int i = 0; i < brojSistemi; i++) {
                os[i] = this->sistemi[i];
            }
            delete [] sistemi;
            os[brojSistemi] = nov;
            brojSistemi++;
            sistemi = os;
        }
    }

};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++) {
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}
