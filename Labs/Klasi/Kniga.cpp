//
// Created by Teodora on 19.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Kniga{
private:
    char ime[100];
    char avtor[100];
    char prezime_avtor[100];
    char ISBN[100];
    int godina;
public:
    Kniga(char i[], char a[], char p[], char isbn[], int g){
        strcpy(ime, i);
        strcpy(avtor, a);
        strcpy(prezime_avtor, p);
        strcpy(ISBN, isbn);
        godina = g;
    }
    Kniga(){}
    ~Kniga(){}
    void set(char i[], char a[], char p[], char isbn[], int g){
        strcpy(ime, i);
        strcpy(avtor, a);
        strcpy(prezime_avtor, p);
        strcpy(ISBN, isbn);
        godina = g;
    }
    int get_year(){
        return godina;
    }
    void display(){
        cout<<"Name: "<<ime<<endl;
        cout<<"Author: "<<avtor<<" "<<prezime_avtor<<endl;
        cout<<"ISBN: "<<ISBN<<endl;
        cout<<"Year: "<<godina<<endl;
    }
};

void booksByOrder(Kniga books[], int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if(books[j].get_year() > books[j+1].get_year()){
                Kniga temp = books[j];
                books[j] = books[j+1];
                books[j+1] = temp;
            }
        }
    }
}

int main(){
    Kniga k("Hamlet", "William", "Shakespeare", "ISBN1234", 1847);
    Kniga book[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[100], avtor[100], prezime[100], ISBN[100];
        int godina;
        cin>>ime>>avtor>>prezime>>ISBN>>godina;
        book[i].set(ime, avtor, ISBN);
    }
    booksByOrder(book, n);
    for (int i = 0; i < n; ++i) {
        book[i].display();
    }
    return 0;
}