//
// Created by Teodora on 29.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class LibraryMameber;
class Library;

class Book{
private:
    char ime[20];
    char avtor[20];
    bool dostapnost;

    friend class Library;
    friend void pecati();
    friend void checkOutBook(LibraryMameber &mameber, Library &libary, int &index);
public:
    Book(char *ime="", char *avtor="", bool dostapnost=true){
        strcpy(this->ime, ime);
        strcpy(this->avtor, avtor);
        this->dostapnost = dostapnost;
    }
    Book(const Book &b){
        strcpy(this->ime, b.ime);
        strcpy(this->avtor, b.avtor);
        this->dostapnost = b.dostapnost;
    }
    ~Book(){}
};

class Library{
private:
    char imeL[20];
    Book knigi[30];
    int br_knigi;

    friend void checkOutBook(LibraryMameber &mameber, Library &library, int &index);
public:
    Library(char *imeL="Brakja Miladinovci"){
        strcpy(this->imeL, imeL);
        br_knigi=0;
    }
    ~Library(){}
    Book addBook(Book &b){
        if(br_knigi < 30){
            knigi[br_knigi++] = b;
        }else{
            cout<<"Bibloteksta e polna"<<endl;
        }
    }
    void pecati(){
        cout<<"Bibloteka: "<<imeL<<endl;
        for (int i = 0; i < br_knigi; ++i) {
            cout<<knigi[i].ime<<" "<<knigi[i].avtor<<" "<<knigi[i].dostapnost<<endl;
        }
    }
};

class LibraryMameber{
private:
    char imeM[20];
    int id;

    friend void checkOutBook(LibraryMameber &mameber, Library &library, int &index);
public:
    LibraryMameber(char *imeM="", int id=0) {
        strcpy(this->imeM, imeM);
        this->id = id;
    }
    ~LibraryMameber(){}
};

void checkOutBook(LibraryMameber &mameber, Library &library, int &index){
    if(library.knigi[index].dostapnost){
        cout<<mameber.imeM<<" ID: "<<mameber.id<<" ckeck out "<<library.knigi[index].ime<<endl;
        library.knigi[index].dostapnost = false;
    }else{
        cout<<"Knigata ne e dostapna"<<endl;
    }
}

int main(){
    Library l;
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[20], avtor[20];
        bool dostapnost;
        cin>>ime>>avtor>>dostapnost;
        Book b(ime, avtor, dostapnost);
        l.addBook(b);
    }
    l.pecati();
    LibraryMameber clen("Damjan", 23);
    int indeks;
    cin>>indeks;
    checkOutBook(clen, l, indeks);
    return 0;
}