//
// Created by Teodora on 14.5.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class HotelskaRezervacija{
protected:
    int brojDenovi;
    int brojLica;
    char ime[50];
    char prezime[50];
public:
    HotelskaRezervacija(char *ime="", char *prezime="", int brojDenovi=0, int brojLica=0){
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->brojDenovi = brojDenovi;
        this->brojLica = brojLica;
    }

    virtual int vratiCena(){
        return brojLica * brojDenovi * 25;
    }

    virtual int vratiCena(int uplata){
         if(uplata >= vratiCena()){
             return uplata - vratiCena();
         }else{
             cout<<"Nema dovolno sredstva za rezervacijata."<<endl;
             return -1;
         }
    }
};

class PolupansionskaHotelskaRezervacija : public HotelskaRezervacija{
public:
    PolupansionskaHotelskaRezervacija(char *ime="", char *prezime="", int brojDenovi=0, int brojLica=0)
    : HotelskaRezervacija(ime, prezime, brojDenovi, brojLica){}

    int vratiCena(int uplata) override{
        int pojadok = HotelskaRezervacija::vratiCena() + (brojLica*5);
        if(uplata >= pojadok){
            return uplata - pojadok;
        }else{
            cout<<"Nema dovolno sredstva za rezervacijata."<<endl;
            return -1;
        }
    }
};

class Hotel{
private:
    char ime[50];
    int saldo;
public:
    Hotel(char *ime="", int saldo=0){
        strcpy(this->ime, ime);
        this->saldo = saldo;
    }

    int uplatiZaRezervacija(HotelskaRezervacija &hr, int uplata){
        int kusur = hr.vratiCena(uplata);
        if(kusur != -1){
            saldo += uplata - kusur;
        }
        return kusur;
    }
};

int main(){
    Hotel h("Bristol");
    HotelskaRezervacija *hr1 = new HotelskaRezervacija("Petko", "Petkovski", 5, 5);
    int cena = h.uplatiZaRezervacija(*hr1, 1000);
    if (cena != -1)
        cout << "Kusur : " << cena << endl;
    PolupansionskaHotelskaRezervacija *hr2 = new PolupansionskaHotelskaRezervacija("Risto", "Ristovski", 5, 5);
    cena = h.uplatiZaRezervacija(*hr2, 1000);
    if (cena != -1){
        cout << "Kusur : " << cena << endl;
    }
    //покажувач кон основна класа покажува кон објект од изведена
    HotelskaRezervacija *hr3 = new PolupansionskaHotelskaRezervacija("Ana", "Anovska", 4, 2);
    cena = h.uplatiZaRezervacija(*hr3, 100);
    if (cena != -1)
        cout << "Kusur : " << cena << endl;
    PolupansionskaHotelskaRezervacija hr4("Tome", "Tomovski", 5, 3);
    cena = h.uplatiZaRezervacija(hr4, 1000);
    if (cena != -1)
        cout << "Kusur : " << cena << endl;
    return 0;
}