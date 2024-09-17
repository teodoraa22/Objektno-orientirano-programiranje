//
// Created by Teodora on 18.4.2024.
//
#include <iostream>
#include <string>
using namespace std;

class TeniskiIgrach{
protected:
    string ime;
    string prezime;
    bool liga;
public:
    TeniskiIgrach(string ime="", string prezime="", bool liga=false){
        this->ime = ime;
        this->prezime = prezime;
        this->liga = liga;
    }
    friend ostream &operator<<(ostream &output, TeniskiIgrach t){
        output<<t.ime<<" "<<t.prezime<<" "<<t.liga;
        return output;
    }
};

class RangiranIgrach : public TeniskiIgrach{
private:
    int rang;
public:
    RangiranIgrach(string ime="", string prezime="", bool liga=false, int rang=0)
    : TeniskiIgrach(ime, prezime, liga){
        this->rang = rang;
    }
    RangiranIgrach(TeniskiIgrach t, int rang=0)
    : TeniskiIgrach(t){
        this->rang = rang;
    }
    friend ostream &operator<<(ostream &o, RangiranIgrach r){
        o<<TeniskiIgrach(r);
        o<<" "<<r.rang<<endl;
        return o;
    }
};

int main(){
    TeniskiIgrach t("Damjan", "Trifunovski", 1);
    cout<<t<<endl;
    RangiranIgrach r1("Davor", "Gjorgievski", 2, 12);
    RangiranIgrach r2(t, 14);
    cout<<r1;
    cout<<r2;
    return 0;
}