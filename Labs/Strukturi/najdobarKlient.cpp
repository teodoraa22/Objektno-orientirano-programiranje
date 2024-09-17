//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
using namespace std;

struct InvoiceItem{
    char id[10];
    int kolicina;
    int cena;

    void read(){
        cin>>id>>kolicina>>cena;
    }
};

struct Invoice{
    char id[10];
    int br_stavki;
    InvoiceItem stavki[100];

    void read(){
        cin>>id>>br_stavki;
        for (int i = 0; i < br_stavki; ++i) {
            stavki[i].read();
        }
    }
};

struct Client{
    char ime[100];
    int br_faktura;
    Invoice fakturi[100];

    void read(){
        cin>>ime>>br_faktura;
        for (int i = 0; i < br_faktura; ++i) {
            fakturi[i].read();
        }
    }
};

void bestClient(Client c[], int n){
    for (int i = 0; i < n; ++i) {
        float vkupno = 0;
        for (int j = 0; j < c[i].br_faktura; ++j) {
            for (int k = 0; k < c[i].fakturi[j].br_stavki; ++k) {
                vkupno += c[i].fakturi[j].stavki[k].cena;
            }
        }
    }
}

int main(){
    Client c[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        c[i].read();
    }
    bestClient(c, n);
    return 0;
}