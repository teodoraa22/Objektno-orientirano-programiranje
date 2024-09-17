//
// Created by Teodora on 20.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Datum{
private:
    int den;
    int mesec;
    int godina;
public:
    Datum(int den, int mesec, int godina){
        this->den = den;
        this->mesec = mesec;
        this->godina = godina;
    }
    Datum(){}
    ~Datum(){}
    void pecati(){
        cout<<den<<"."<<mesec<<"."<<godina<<endl;
    }
    int get_den(){
        return den;
    }
    int get_mesec(){
        return mesec;
    }
    int get_godina(){
        return godina;
    }
};

class Vraboten{
private:
    char ime[20];
    int plata;
    Datum datum;
public:
    Vraboten(char ime[], int plata, Datum datum){
        strcpy(this->ime, ime);
        this->plata = plata;
        this->datum = datum;
    }
    Vraboten(){}
    ~Vraboten(){}
    void set_se(char ime[], int plata, Datum datum){
        strcpy(this->ime, ime);
        this->plata = plata;
        this->datum = datum;
    }
    void pecati(){
        cout<<ime<<" "<<plata<<" ";
        datum.pecati();
    }
    int get_plata(){
        return plata;
    }
    Datum get_datumRagjanje(){
        return datum;
    }
};

Vraboten najgolema_plata(Vraboten niza[], int n){
    Vraboten max = niza[0];
    for (int i = 1; i < n; ++i) {
        if (niza[i].get_plata() > niza[0].get_plata()){
            max = niza[i];
        }
    }
    return max;
}

//-1=prviot e postar, 0-isti se, 1=vtoriot e postar

int datum(Datum d1, Datum d2){
    if(d1.get_godina() > d2.get_godina()){
        return 1;
    }else if(d1.get_godina() < d2.get_godina()){
        return -1;
    }else if(d1.get_mesec() > d2.get_mesec()) {
        return 1;
    }else if(d1.get_mesec() < d2.get_mesec()){
        return -1;
    }else if(d1.get_den() > d2.get_den()){
        return 1;
    }else if(d1.get_den() < d2.get_den()){
        return -1;
    }else{
        return 0;
    }
}

Vraboten najmlad_vraboten(Vraboten niza[], int n){
    Datum min = niza[0].get_datumRagjanje();
    Vraboten najmlad = niza[0];
    for (int i = 1; i < n; ++i) {
        if(datum(niza[i].get_datumRagjanje(), niza[0].get_datumRagjanje()) == 1){
            min = niza[i].get_datumRagjanje();
            najmlad = niza[i];
        }
    }
    return najmlad;
}

int main(){
    Vraboten vraboten[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[20];
        int plata, den, mesec, godina;
        cin>>ime>>plata>>den>>mesec>>godina;
        Datum d(den, mesec, godina);
        vraboten[i].set_se(ime, plata, d);
    }
    cout<<"Najgolema plata: ";
    najgolema_plata(vraboten, n).pecati();
    cout<<"Najmlad vraboten: ";
    najmlad_vraboten(vraboten, n).pecati();
    return 0;
}