//
// Created by Teodora on 13.3.2024.
//
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Momche{
private:
    char ime[30];
    char prezime[30];
    int godini;
public:
    Momche(char i[], char p[], int g){
        strcpy(ime, i);
        strcpy(prezime, p);
        godini = g;
    }
    Momche(){}
    ~Momche(){}
    void pecati(){
        cout<<"Momche: "<<ime<<" "<<prezime<<" "<<godini<<" ";
    }
    int get_godini(){
        return godini;
    }
};

class Devojche{
private:
    char ime[30];
    char prezime[30];
    int godini;
public:
    Devojche(char i[], char p[], int g){
        strcpy(ime, i);
        strcpy(prezime, p);
        godini = g;
    }
    Devojche(){}
    ~Devojche(){}
    void pecati(){
        cout<<"Devojche: "<<ime<<" "<<prezime<<" "<<godini<<endl;
    }
    int get_godini(){
        return godini;
    }
};

class Sredba{
private:
    Momche momche;
    Devojche devojche;
public:
    Sredba(Momche m, Devojche d){
        momche = m;
        devojche = d;
    }
    ~Sredba(){}
    void pecati(){
        cout<<"Sredba: ";
        momche.pecati();
        devojche.pecati();
    }
    void dali_si_odgovaraat(){
        if(abs(momche.get_godini()-devojche.get_godini()) < 5){
            cout<<"Si odgovaraat"<<endl;
        }else{
            cout<<"Ne si odgovaraat"<<endl;
        }
    }
};

int main(){
    char ime[30], prezime[30];
    int godini;
    cin>>ime>>prezime>>godini;
    Momche m(ime, prezime, godini);
    cin>>ime>>prezime>>godini;
    Devojche d(ime, prezime, godini);
    Sredba s(m, d);
    s.pecati();
    s.dali_si_odgovaraat();
    return 0;
}