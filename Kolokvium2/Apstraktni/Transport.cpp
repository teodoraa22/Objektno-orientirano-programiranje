//
// Created by Teodora on 02.6.2024.
//
// вашиот код треба да биде тука
#include<iostream>
#include<cstring>

using namespace std;

class Transport{
protected:
    char destinacija[20];
    int cena;
    int kilometraza;
public:
    Transport(char *destinacija="", int cena=0, int kilometraza=0){
        strcpy(this->destinacija, destinacija);
        this->cena = cena;
        this->kilometraza = kilometraza;
    }

    virtual float cenaTransport() = 0;

    bool operator<(Transport &other){
        return kilometraza < other.kilometraza;
    }

    virtual void pecati(){
        cout << destinacija << " " << kilometraza << " " << cenaTransport() << endl;
    }

};

class AvtomobilTransport : public Transport{
private:
    bool sofer;
public:
    AvtomobilTransport(char *destinacija="", int cena=0, int kilometraza=0, bool sofer=true)
    : Transport(destinacija, cena, kilometraza){
        this->sofer = sofer;
    }

    float cenaTransport() override{
        if(sofer){
            return cena * 1.2;
        }
        return cena;
    }
};

class KombeTransport : public Transport{
private:
    int broj_lugje;
public:
    KombeTransport(char *destinacija="", int cena=0, int kilometraza=0, int broj_lugje=0)
    : Transport(destinacija, cena, kilometraza){
        this->broj_lugje = broj_lugje;
    }

    float cenaTransport() override{
        float price = cena - broj_lugje * 200;
        if (price < 0) {
            return 0;
        }
        return price;
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, AvtomobilTransport T) {
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if(ponudi[i]->cenaTransport() > ponudi[j]->cenaTransport()){
                swap(ponudi[i], ponudi[j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if(ponudi[i]->cenaTransport() > T.cenaTransport()){
            ponudi[i]->pecati();
        }
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
