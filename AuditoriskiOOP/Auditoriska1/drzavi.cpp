//
// Created by Teodora on 05.3.2024.
//
#include<iostream>
using namespace std;

struct Grad{
    char ime[50];
    int br_ziteli;

    void read(){
        cin>>ime>>br_ziteli;
    }

    void print(){
        cout<<"Grad: "<<ime<<" Broj na ziteli vo gradot: "<<br_ziteli<<endl;
    }
};

struct Pretsedatel{
    char ime[50];
    char prezime[50];
    char partija;

    void read(){
        cin>>ime>>prezime>>partija;
    }

    void print(){
        cout<<"Ime na pretsedatel: "<<ime<<" Prezime: "<<prezime<<" Partija: "<<partija<<endl;
    }
};

struct Drzava{
    char ime[50];
    Pretsedatel pretsedatel;
    Grad gl_grad;
    int br_ziteli;

    void read(){
        cin>>ime;
        pretsedatel.read();
        gl_grad.read();
        cin>>br_ziteli;
    }

    void print(){
        cout<<"Drzava: "<<ime<<endl;
        pretsedatel.print();
        gl_grad.print();
        cout<<"Broj na ziteli vo drzavata: "<<br_ziteli<<endl;
    }
};

int main(){
    Drzava drzavi[100];
    int n;
    cin>>n;

    for (int i = 0; i < n; ++i) {
        drzavi[i].read();
        drzavi[i].print();
    }

    Drzava max = drzavi[0];
    for (int i = 0; i < n; ++i) {
        if(drzavi[i].gl_grad.br_ziteli > max.gl_grad.br_ziteli){
            max = drzavi[i];
        }
    }

    cout<<max.pretsedatel.ime<<" "<<max.pretsedatel.prezime;
    return 0;
}