//
// Created by Teodora on 18.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class BasketballPlayer{
private:
    char ime[20];
    char prezime[20];
    int br_dres;
    int poeni1;
    int poeni2;
    int poeni3;
public:
    BasketballPlayer(char i[], char p[], int d, int p1, int p2, int p3){
        strcpy(ime, i);
        strcpy(prezime, p);
        br_dres = d;
        poeni1 = p1;
        poeni2 = p2;
        poeni3 = p3;
    }
    ~BasketballPlayer(){}
    void pecati(){
        cout<<"Player: "<<ime<<" "<<prezime<<" with number: "<<br_dres<<" has "<<(poeni1 + poeni2 + poeni3)/3<<" points on average";
    }
};

int main(){
    char ime[20], prezime[20];
    int dres, poeni1, poeni2, poeni3;
    cin>>ime>>prezime>>dres>>poeni1>>poeni2>>poeni3;
    BasketballPlayer player(ime, prezime, dres, poeni1, poeni2, poeni3);
    player.pecati();
    return 0;
}