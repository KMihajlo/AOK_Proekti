#include<iostream>
#include<string.h>
using namespace std;

class BadInputException : public exception {};

class StudentKurs {
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
public:
    StudentKurs(char* ime,int finalenIspit) {
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    static void setMAX (int max) {
        MAX = max;
    }
    bool getDaliUsno() {
        return daliUsno;
    }
    virtual int grade () {
        return ocenka;
    }
    virtual ~StudentKurs () {}

    virtual StudentKurs& operator += (char *op) {
        return *this;
    }

    friend ostream& operator << (ostream &x, StudentKurs &s) {
        x << s.ime << " --- "<<s.grade()<<endl;
        return x;
    }
    char *getIme () {
        return ime;
    }
};
int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs {
private:
    char *opisna;
public:
    StudentKursUsno(char* ime,int finalenIspit)
        : StudentKurs (ime,finalenIspit) {
        daliUsno = true;
    }
    int grade () {
        if(strcmp(opisna,"odlicen")==0&&ocenka+2 <= MAX)
            return StudentKurs::grade() + 2;
        if(strcmp(opisna,"dobro")==0&&ocenka+1 <= MAX)
            return StudentKurs::grade () + 1;
        if(strcmp(opisna,"losho")==0 && ocenka-1 <= MAX)
            return StudentKurs::grade () - 1;
        return StudentKurs::grade ();
    }
    ~StudentKursUsno () {
        delete [] opisna;
    }
    friend ostream& operator << (ostream &x, StudentKursUsno &s) {
        x << s.ime << " --- "<<s.grade()<<endl;
        return x;
    }
    StudentKursUsno& operator += (char *op) {

        opisna = new char [strlen(op)+1];
        int flag = 0,k=0;
        for(int i=0; i<strlen(op); i++) {
            if(isalpha(op[i])) {
                opisna[k]=op[i];
                k++;
            } else flag = 1;
        }

        if(flag)
            throw BadInputException();

        return *this;
    }
};


class KursFakultet {
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    static const int MINOCENKA = 6;
public:
    KursFakultet(const char *naziv, StudentKurs** studenti,int broj ) {
        strcpy(this->naziv,naziv);
        for (int i=0; i<broj; i++) {
            if (studenti[i]->getDaliUsno()) {
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            } else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet() {
        for (int i=0; i<broj; i++) delete studenti[i];
    }

    void pecatiStudenti () {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0; i<broj; i++) {
            if(studenti[i]->grade()>=MINOCENKA)
                cout<<*studenti[i];
        }

    }
    void postaviOpisnaOcenka (char *ime, char *opisnaOcenka) {
        for(int i=0; i<broj; i++) {
            if(strcmp(ime,studenti[i]->getIme())==0)
                *studenti[i]+=opisnaOcenka;
        }
    }
};

int main() {

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0; i<n; i++) {
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0; i<n; i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0; i<m; i++) {
        cin>>ime>>opisna;
        try {
            programiranje.postaviOpisnaOcenka(ime,opisna);
        } catch (exception &e) {
            cout<<"Greshna opisna ocenka"<<endl;
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
