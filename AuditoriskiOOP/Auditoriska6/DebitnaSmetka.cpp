//
// Created by Teodora on 18.4.2024.
//
#include <iostream>
#include <string>
using namespace std;

class DebitnaSmetka{
protected:
    string ime;
    string prezime;
    long int broj;
    double saldo;
public:
    DebitnaSmetka(string ime="", string prezime="", long int broj=0, double saldo=0){
        this->ime = ime;
        this->prezime = prezime;
        this->broj = broj;
        this->saldo = saldo;
    }
    DebitnaSmetka(const DebitnaSmetka &db){
        this->ime = db.ime;
        this->prezime = db.prezime;
        this->broj = db.broj;
        this->saldo = db.saldo;
    }
    void pregled(){
        cout<<ime<<" "<<prezime<<" "<<broj<<" "<<saldo;
    }
    void deponiranje(double suma){
        if(suma > 0){
            saldo += suma;
        }else{
            cout<<"Nevalidna uplata!"<<endl;
        }
    }
    void podignuvanje(double suma){
        if(suma <= saldo){
            saldo -= suma;
        }else{
            cout<<"Nevalidna isplata!"<<endl;
        }
    }
};

class KreditnaSmetka : public DebitnaSmetka{
private:
    double limit;
    double kamata;
    double minus;
public:
    KreditnaSmetka(string ime="", string prezime="", long int broj=0, double saldo=0, double limit=0, double kamata=0, double minus=0)
    : DebitnaSmetka(ime, prezime, broj, saldo){
        this->limit = limit;
        this->kamata = kamata;
        this->minus = minus;
    }
    KreditnaSmetka(const DebitnaSmetka &db)
    : DebitnaSmetka(db){
        this->limit = limit;
        this->kamata = kamata;
        this->minus = minus;
    }
    void pecati(){
        DebitnaSmetka::pregled();
        cout<<" "<<limit<<" "<<kamata<<" "<<minus<<endl;
    }
    void deponiranje(double suma){
        if(suma <= minus){
            minus -= suma;
        }else{
            saldo += (suma-minus);
            minus = 0;
        }
    }
    void podignuvanje(double suma){
        if(saldo >= suma){
            DebitnaSmetka::podignuvanje(suma);
        }else{
            double razlika = suma-saldo;
            if((razlika+minus) < limit){
                saldo = 0;
                minus += (razlika * (1.0 * kamata));
            }
        }
    }
};

int main(){
    DebitnaSmetka d("Teodora", "Gjorgievska", 1234293912, 5000);
    d.pregled();
    cout<<endl;
    d.deponiranje(3000);
    d.podignuvanje(2000);
    KreditnaSmetka k("Davor", "Gjorgievski", 218903221, 6000, 1500, 5, 0);
    k.pecati();
    k.deponiranje(2000);
    k.podignuvanje(8000);
    k.pecati();
    return 0;
}
