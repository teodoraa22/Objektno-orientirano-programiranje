//
// Created by Teodora on 01.6.2024.
//
#include<iostream>
#include<string>
using namespace std;

//klasa za iskluchoci, najcesto ima edna podatochna chlenka najchesto nekoja poraka/tekst
class NegativeValueException{
private:
    string message;
public:
    NegativeValueException(string message=""){
        this->message = message;
    }
    void print(){
        cout<<message<<endl;
    }
};

class Discount{
protected:
     static float euro;
     static float dolar;
public:
    virtual float discount_price() = 0;
    virtual float price() = 0;
    virtual void print_rule() = 0;
};

float Discount::euro = 61.7;
float Discount::dolar = 44.5;

class Product{
protected:
    string ime;
    float cena;
public:
    Product(string ime="", float cena=0){
        this->ime = ime;
        this->cena = cena;
    }
    void changePrice(double newPrice){
        if(newPrice<0){
            //frla isklucok
            throw NegativeValueException("Vnesena e negativna vrednost!");
        }else{
            this->cena = newPrice;
        }
    }
    void pecati(){
        cout<<"Produkt: "<<ime<<" Cena: "<<cena<<endl;
    }
};

class FoodProduct : public Discount, public Product{
private:
    int kalorii;
public:
    FoodProduct(string ime="", float cena=0, int kalorii=0)
    : Product(ime, cena){
        this->kalorii = kalorii;
    }
    float discount_price(){
        return cena;
    }
    float price(){
        return cena;
    }
    void print_rule(){
        cout<<"Spored novata politika na prodavnicata za hranata nema popust. "<<endl;
    }
};

class Drinks : public Discount, public Product{
private:
    string brend;
    bool alkoholen;
public:
    Drinks(string ime="", float cena=0, string brend="", bool alkoholen=false)
    : Product(ime, cena){
        this->brend = brend;
        this->alkoholen = alkoholen;
    }
    float discount_price(){
        if(alkoholen && cena/Discount::euro > 20){
            return cena * 0.95;
        }else if(!alkoholen && brend=="Coca-Cola"){ //brend.compare("Coca-Cola)==0
            return cena * 0.9;
        }else{
            return cena;
        }
    }
    float price(){
        return cena;
    }
    void print_rule(){
        cout<<"Pijalocite i toa alkoholnite poskapi od 20 evra imaat popust 5%, a nealkoholnite od brendot Coca-Cola imaat popust od 10%. "<<endl;
    }
};

class Cosmetics : public Discount, public Product{
private:
    int tezina;
public:
    Cosmetics(string ime="", float cena=0, int tezina=0)
    : Product(ime, cena){
        this->tezina = tezina;
    }
    float discount_price(){
        if(cena/Discount::dolar > 20){
            return cena * 0.86;
        }else if(cena/Discount::euro > 5){
            return cena * 0.88;
        }else{
            return cena;
        }
    }
    float price(){
        return cena;
    }
    void print_rule(){
        cout<<"Site kozmeticki proizvodi poskapi od 5 evra imaat 12% popust, a onie poskapi od 20 dolari imaat popust 14%. "<<endl;
    }
};

float total_Discount(Discount **d, int n){
    float popust=0;
    for (int i = 0; i < n; ++i) {
        popust += d[i]->discount_price();
        cout<<"Osnovna cena: "<<d[i]->price()<<endl;
        cout<<"Cena so popust: "<<d[i]->discount_price()<<endl;
        d[i]->print_rule();
    }
    return popust;
}

int main(){
    int n;
    cin>>n;
    Discount **d = new Discount * [n];
    int type;
    string ime, brend;
    bool alkoholen;
    float cena;
    int kalorii, tezina;
    for (int i = 0; i < n; ++i) {
        cin>>type;
        if(type==1){
            cin>>ime>>cena>>kalorii;
            d[i] = new FoodProduct(ime, cena, kalorii);
        }else if(type==2){
            cin>>ime>>cena>>brend>>alkoholen;
            d[i] = new Drinks(ime, cena, brend, alkoholen);
        }else if(type==3){
            cin>>ime>>cena>>tezina;
            d[i] = new Cosmetics(ime, cena, tezina);
        }
    }
    float novaCena;
    cout<<"Vkupna cena na site proizvodi e: "<<total_Discount(d, n);
    //niza d i za site discounti tie sto se tip kozmetika da ja povikame funkcijata exseption so try i catch
    for (int i = 0; i < n; ++i) {
        Cosmetics *pok =dynamic_cast<Cosmetics *>(d[i]);
        if(pok){
            pok->pecati();
            cin>>novaCena;
            //try = kje ja povikame funkcijata changePrice
            try{
                pok->changePrice(novaCena);
            }
            //catch = kje ja povikame print funkcijata za da ja ispecatime porakta koja se naogja vo klasata za exception
            catch(NegativeValueException ex){
                ex.print();
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        delete d[i];
    }
    delete[] d;
    return 0;
}