#include <iostream>
#include <cstring>
using namespace std;

class Book
{
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    float cena;
public:
    Book(char *ISBN = "", char *naslov = "", char *avtor = "", float cena = 0.0)
    {
        strcpy(this->ISBN, ISBN);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena = cena;
    }
    friend ostream &operator<<(ostream &out, Book &b)
    {
        out << b.ISBN << ": " << b.naslov << ", " << b.avtor << " " << b.bookPrice() << endl;
        return out;
    }
    virtual ~Book(){}
    virtual float bookPrice() = 0;
};
bool operator>(Book &b1, Book &b2)
{
    if(b1.bookPrice() > b2.bookPrice())
        return true;
    else
        return false;
}
class OnlineBook : public Book
{
private:
    char *url;
    int golemina;
public:
    OnlineBook(char *ISBN = "", char *naslov = "", char *avtor = "", float cena = 0.0, char *url = "", int golemina = 0)
    : Book(ISBN, naslov, avtor, cena)
    {
        this->url = new char[strlen(url)+1];
        strcpy(this->url, url);
        this->golemina = golemina;
    }
    OnlineBook(OnlineBook &o)
    {
        strcpy(this->ISBN, o.ISBN);
        strcpy(this->naslov, o.naslov);
        strcpy(this->avtor, o.avtor);
        this->cena = o.cena;
        this->url = new char[strlen(o.url)+1];
        strcpy(this->url, o.url);
        this->golemina = o.golemina;
    }
    OnlineBook &operator=(OnlineBook &o)
    {
        if(this!=&o)
        {
            strcpy(this->ISBN, o.ISBN);
            strcpy(this->naslov, o.naslov);
            strcpy(this->avtor, o.avtor);
            this->cena = o.cena;
            delete [] url;
            this->url = new char[strlen(o.url)+1];
            strcpy(this->url, o.url);
            this->golemina = o.golemina;
        }
        return *this;
    }
    ~OnlineBook()
    {
        delete [] url;
    }
    void setISBN(char *ISBN)
    {
        strcpy(this->ISBN, ISBN);
    }
    float bookPrice()
    {
        if(golemina > 20)
            return cena*1.2;
        else
            return cena;
    }
};
class PrintBook : public Book
{
private:
    float masa;
    bool daliJaIma;
public:
    PrintBook(char *ISBN = "", char *naslov = "", char *avtor = "", float cena = 0.0, float masa = 0.0, bool daliJaIma = false)
    : Book(ISBN, naslov, avtor, cena)
    {
        this->masa = masa;
        this->daliJaIma = daliJaIma;
    }
    float bookPrice()
    {
        if(masa > 0.7)
            return cena*1.15;
        else
            return cena;
    }
};
void mostExpensiveBook(Book** books, int n)
{
    int sumOnline = 0;
    int sumPrinted = 0;
    Book *bla = books[0];
    for(int i = 0; i < n; i++)
    {
        if(books[i]->bookPrice() > bla->bookPrice())
        {
            bla = books[i];
        }
        OnlineBook *kniga1 = dynamic_cast<OnlineBook *>(books[i]);
        if(kniga1 != 0)
        {
            sumOnline++;
        }
        PrintBook *kniga2 = dynamic_cast<PrintBook *>(books[i]);
        if(kniga2!=0)
        {
            sumPrinted++;
        }
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << sumOnline << endl;
    cout << "Total number of print books: " << sumPrinted << endl;
    cout << "The most expensive book is: " << endl;
    cout << *bla << endl;
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
