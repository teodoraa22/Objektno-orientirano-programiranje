//
// Created by Teodora on 16.5.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Discount{
public:
    virtual double getCena() = 0;
    virtual double cenaSoPopust() = 0;
};

class Product{
protected:
    string ime;
    double cena;
public:
    Product(string ime="", double cena = 0){
        this->ime = ime;
        this-> cena = cena;
    }

    double getCena(){
        return cena;
    }
};

class FoodProduct : public Product, public Discount{
private:
    int kalorii;
public:
    FoodProduct(string ime="", double cena = 0, int kalorii = 0)
    : Product(ime, cena){
        this->kalorii = kalorii;
    }

    double getCena(){
        return Product::getCena();
    }

    double cenaSoPopust(){
        return 0.8 * getCena();
    }
};

class DigitalProduct : public Product, public Discount{
private:
    int golemina;
public:
    DigitalProduct(string ime="", double cena = 0, int golemina = 0)
    : Product(ime, cena){
        this->golemina = golemina;
    }

    double getCena(){
        return Product::getCena();
    }

    double cenaSoPopust(){
        return 0.9 * getCena();
    }
};

double total_discount(Discount **d, int n){
    double cena = 0;
    for (int i = 0; i < n; ++i) {
        cena += d[i]->getCena();
    }

    double popust = 0;
    for (int i = 0; i < n; ++i) {
        popust += d[i]->cenaSoPopust();
    }

    return cena - popust;
}

int main(){
    Discount **d = new Discount*[3];
    d[0] = new FoodProduct("Cheese", 450, 1200);
    d[1] = new FoodProduct("Wine", 780, 250);
    d[2] = new DigitalProduct("WOW", 380, 400);
    cout << "Difference: " << total_discount(d, 3) << endl;
    for (int i = 0; i < 3; ++i) {
        delete d[i];
    }
    delete[] d;
    return 0;
}