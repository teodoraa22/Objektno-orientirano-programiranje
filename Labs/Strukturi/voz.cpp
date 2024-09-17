//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

struct Voz{
    char relacija[50];
    float km;
    int br_patnici;
};

struct ZeleznickaStanica{
    char grad[20];
    Voz vozovi[30];
    int br_vozovi;

    void read(){
        cin>>grad>>br_vozovi;
        for (int i = 0; i < br_vozovi; ++i) {
            cin>>vozovi[i].relacija>>vozovi[i].km>>vozovi[i].br_patnici;
        }
    }
};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad){
    float kilometri;
    char najkratka[50];
    for (int i = 0; i < n; ++i) {
        kilometri = zs[i].vozovi[0].km;
        if (strcmp(zs[i].grad, grad) == 0) {
            for (int j = 0; j < zs[i].br_vozovi; ++j) {
                if (zs[i].vozovi[j].km < kilometri){
                    kilometri = zs[i].vozovi[j].km;
                    strcpy(najkratka, zs[i].vozovi[j].relacija);
                }
            }
            cout<<"Najkratka relacija: "<<najkratka<<" ("<<kilometri<<" km)"<<endl;
        }
    }
}

int main(){
    ZeleznickaStanica zs[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        zs[i].read();
    }
    char grad[30];
    cin>>grad;
    najkratkaRelacija(zs, n, grad);
    return 0;
}