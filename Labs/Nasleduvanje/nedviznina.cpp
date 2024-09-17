//
// Created by Teodora on 26.4.2024.
//
#include <iostream>
#include <cstring>
using namespace std;

class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int cena_kvadrat;
public:
    Nedviznina(char *adresa="", int kvadratura=0, int cena_kvadrat=0){
        this->adresa = new char[strlen(adresa)+1];
        this->kvadratura = kvadratura;
        this->cena_kvadrat = cena_kvadrat;
    }

    Nedviznina(const Nedviznina &n){
        this->adresa = new char[strlen(n.adresa)+1];
        this->kvadratura = n.kvadratura;
        this->cena_kvadrat = n.cena_kvadrat;
    }

    Nedviznina &operator=(const Nedviznina &n){
        if(this!=&n){
            delete [] adresa;
            this->adresa = new char[strlen(n.adresa)+1];
            this->kvadratura = n.kvadratura;
            this->cena_kvadrat = n.cena_kvadrat;
        }
        return *this;
    }

    ~Nedviznina(){
        delete [] adresa;
    }

    int cena(){
        return kvadratura * cena_kvadrat;
    }

    void pecati(){
        cout<<adresa<<" "<<kvadratura<<" "<<cena_kvadrat;
    }

    double danokNaImot(){
        return cena() * 0.5;
    }

    friend ostream &operator<<(ostream &out, Nedviznina n){
        out<<n.adresa<<" "<<n.kvadratura<<" "<<n.cena_kvadrat;
        return out;
    }

    char *getAdresa(){
        return adresa;
    }
};

class Vila : public Nedviznina{
private:
    int luksuz;
public:
    Vila(char *adresa="", int kvadratura=0, int cena_kvadrat=0, int luksuz=0)
    : Nedviznina(adresa, kvadratura, cena_kvadrat){
        this->luksuz = luksuz;
    }

    void pecati(){
        Nedviznina::pecati();
        cout<<" "<<luksuz<<endl;
    }

    double danokNaImot(){
        return Nedviznina::danokNaImot() * luksuz;
    }

    friend ostream &operator<<(ostream &o, Vila v){
        o<<Nedviznina(v);
        o<<" "<<v.luksuz<<endl;
    }
};

int main(){
    Nedviznina n("adresa", 10, 5);
    Vila v("adresa", 10, 5, 4);
    v.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}