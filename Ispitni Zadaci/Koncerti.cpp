#include<iostream>
#include<string.h>
using namespace std;

class Koncert
{
private:
    char naziv[20];
    char lokacija[20];
    static float popust;
    float cenaBilet;
public:
    Koncert(char *naziv = "", char *lokacija = "", float cenaBilet = 0.0)
    {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->cenaBilet = cenaBilet;
    }
    virtual float cena()
    {
        return cenaBilet * (1-popust);
    }
    static void setSezonskiPopust(float broj)
    {
        popust = broj;
    }
    static float getSezonskiPopust()
    {
        return popust;
    }
    char *getNaziv()
    {
        return naziv;
    }
    char *getLokacija()
    {
        return lokacija;
    }
    float getCenaBilet()
    {
        return cenaBilet;
    }
    void setNaziv(char *bla)
    {
        strcpy(this->naziv, bla);
    }
    void setLokacija(char *bla)
    {
        strcpy(this->lokacija, bla);
    }
    void setCenaBilet(float bla)
    {
        this->cenaBilet = bla;
    }
    virtual ~Koncert(){}
};
float Koncert::popust = 0.2;
class ElektronskiKoncert : public Koncert
{
private:
    char *imeDJ;
    float vremetraenje;
    bool kakvaZabava;
public:
    ElektronskiKoncert(char *naziv = "", char *lokacija = "", float cenaBilet = 0.0, char *imeDJ = "", float vremetraenje = 0.0, bool kakvaZabava = false)
    : Koncert(naziv, lokacija, cenaBilet)
    {
        this->imeDJ = new char[strlen(imeDJ)+1];
        strcpy(this->imeDJ, imeDJ);
        this->vremetraenje = vremetraenje;
        this->kakvaZabava = kakvaZabava;
    }
    ElektronskiKoncert(ElektronskiKoncert &e)
    {
        Koncert::setNaziv(e.getNaziv());
        Koncert::setLokacija(e.getLokacija());
        Koncert::setCenaBilet(e.getCenaBilet());
        this->imeDJ = new char[strlen(e.imeDJ)+1];
        strcpy(this->imeDJ, e.imeDJ);
        this->vremetraenje = e.vremetraenje;
        this->kakvaZabava = e.kakvaZabava;
    }
    ElektronskiKoncert&operator=(ElektronskiKoncert &e)
    {
        if(this!=&e)
        {
            Koncert::setNaziv(e.getNaziv());
            Koncert::setLokacija(e.getLokacija());
            Koncert::setCenaBilet(e.getCenaBilet());
            delete [] imeDJ;
            this->imeDJ = new char[strlen(e.imeDJ)+1];
            strcpy(this->imeDJ, e.imeDJ);
            this->vremetraenje = e.vremetraenje;
            this->kakvaZabava = e.kakvaZabava;
        }
        return *this;
    }
    ~ElektronskiKoncert()
    {
        delete [] imeDJ;
    }
    float cena()
    {
        float sum = Koncert::cena();
        if(kakvaZabava == true)
        {
            sum = sum - 50;
            if(vremetraenje > 5.0 && vremetraenje < 7.0)
            {
                sum = sum + 150;
            }
            if(vremetraenje >= 7.0)
            {
                sum = sum + 360;
            }
        }
        else
        {
            sum = sum + 100;
            if(vremetraenje >= 5.0 && vremetraenje < 7.0)
            {
                sum = sum + 150;
            }
            if(vremetraenje >= 7.0)
            {
                sum = sum + 360;
            }
        }
        return sum;
    }
};
void najskapKoncert(Koncert **koncerti, int n)
{
    float max = 0.0;
    int id = 0, count = 0;
    for(int i = 0; i < n; i++)
    {
        if(koncerti[i]->cena() > max)
        {
            max = koncerti[i]->cena();
            id = i;
        }

        ElektronskiKoncert *tmp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if(tmp!=0)
        {
            count++;
        }
    }
    cout<<"Najskap koncert: ";
    cout << koncerti[id]->getNaziv() << " " << koncerti[id]->cena() << endl;
    cout << "Elektronski koncerti: " << count << " od vkupno " << n << endl;
}
bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski)
{
    bool var = false;
    for(int i = 0; i < n; i++)
    {
        if(elektronski == true)
        {
            ElektronskiKoncert *tmp = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if(tmp!=0)
            {
                if(strcmp(koncerti[i]->getNaziv(), naziv) == 0)
                {
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    var = true;
                }
            }
        }
        else
        {
            if(strcmp(koncerti[i]->getNaziv(), naziv) == 0)
            {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                var = true;
            }
        }
    }
    return var;
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}
