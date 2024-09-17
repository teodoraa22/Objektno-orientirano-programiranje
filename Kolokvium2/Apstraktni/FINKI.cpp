//
// Created by Teodora on 02.6.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Book{
protected:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    double cena;
public:
    Book(char *ISBN="", char *naslov="", char *avtor="", double cena=0){
        strcpy(this->ISBN, ISBN);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->cena = cena;
    }

    virtual double bookPrice()=0;

    bool operator>(Book &f){
        return this->bookPrice() > f.bookPrice();
    }

    friend ostream &operator<<(ostream &o, Book &f){
        o<<f.ISBN<<": "<<f.naslov<<", "<<f.avtor<<" "<<f.bookPrice()<<endl;
        return o;
    }
};

class OnlineBook : public Book{
private:
    char *url;
    int golemina; //MB
public:
    OnlineBook(char *ISBN="", char *naslov="", char *avtor="", double cena=0, char *url="", int golemina=0)
    : Book(ISBN, naslov, avtor, cena){
        this->url = new char[strlen(url)+1];
        strcpy(this->url, url);
        this->golemina = golemina;
    }

    OnlineBook(const OnlineBook &ob){
        strcpy(this->ISBN, ob.ISBN);
        strcpy(this->naslov, ob.naslov);
        strcpy(this->avtor, ob.avtor);
        this->cena = ob.cena;
        this->url = new char[strlen(ob.url)+1];
        strcpy(this->url, ob.url);
        this->golemina = ob.golemina;
    }

    OnlineBook &operator=(const OnlineBook &ob){
        if(this!=&ob){
            delete [] this->url;
            strcpy(this->ISBN, ob.ISBN);
            strcpy(this->naslov, ob.naslov);
            strcpy(this->avtor, ob.avtor);
            this->cena = ob.cena;
            this->url = new char[strlen(ob.url)+1];
            strcpy(this->url, ob.url);
            this->golemina = ob.golemina;
        }
        return *this;
    }

    double bookPrice() override{
        if(golemina > 20){
            return cena*1.2;
        }
        return cena;
    }

    friend ostream &operator<<(ostream &o, OnlineBook &ob){
        o<<ob.ISBN<<": "<<ob.naslov<<", "<<ob.avtor<<" "<<ob.bookPrice()<<endl;
        return o;
    }

    ~OnlineBook(){
        delete [] url;
    }

    void setISBN(char *string) {
        strcpy(ISBN, string);
    }
};


class PrintBook : public Book{
private:
    double masa;
    bool na_zaliha;
public:
    PrintBook(char *ISBN="", char *naslov="", char *avtor="", double cena=0, double masa=0, bool na_zaliha=false)
    : Book(ISBN, naslov, avtor, cena){
        this->masa = masa;
        this->na_zaliha = na_zaliha;
    }

    double bookPrice() override{
        if(masa > 0.7){
            return cena*1.15;
        }
        return cena;
    }

    friend ostream &operator<<(ostream &o, PrintBook &pb){
        o<<pb.ISBN<<": "<<pb.naslov<<", "<<pb.avtor<<" "<<pb.bookPrice()<<endl;
        return o;
    }
};

void mostExpensiveBook (Book** books, int n){
    int online = 0;
    int print = 0;
    Book *mostExpensive = books[0];
    for (int i = 0; i < n; ++i) {
        if(dynamic_cast<OnlineBook *>(books[i])){
            online++;
        }else if(dynamic_cast<PrintBook *>(books[i])){
            print++;
        }
        if(books[i]->bookPrice() > mostExpensive->bookPrice()){
            mostExpensive = books[i];
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<print<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*mostExpensive<<endl;
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
