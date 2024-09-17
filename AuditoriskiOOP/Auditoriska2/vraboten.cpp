//
// Created by Teodora on 13.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

enum pozicija{
    vraboten, direktor, sef   // 0, 1, 2
};

class Vraboten{
private:
    char ime[30];
    int plata;
    pozicija p;
public:
    Vraboten(char i[], int pl, pozicija pp){
        strcpy(ime, i);
        plata = pl;
        p = pp;
    }
    Vraboten(){}
    ~Vraboten(){}
    void pecati(){
        cout<<ime<<" "<<plata<<endl;
    }
    void set_se(char i[], int pl, int pp){
        strcpy(ime, i);
        plata = pl;
        p = (pozicija)pp;
    }
    int get_plata(){
        return plata;
    }
};

void bubblesort(Vraboten niza[], int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if(niza[j].get_plata() < niza[j+1].get_plata()){
                Vraboten temp = niza[j];
                niza[j] = niza[j+1];
                niza[j+1] = temp;
            }
        }
    }
}

int main(){
    Vraboten v("Teodora", 15, (pozicija)0);
    Vraboten niza[5];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[30];
        int plata, p;
        cin>>ime>>plata>>p;
        niza[i].set_se(ime, plata, p);
    }
    bubblesort(niza, n);
    for (int i = 0; i < n; ++i) {
        niza[i].pecati();
    }
    return 0;
}