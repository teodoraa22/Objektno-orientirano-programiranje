//
// Created by Teodora on 25.4.2024.
//
#include <iostream>
#include <cstring>
using namespace std;

class Ekipa{
protected:
    char ime[15];
    int br_pobedi;
    int br_porazi;
public:
    Ekipa(char ime[]="", int br_pobedi=0, int br_porazi=0){
        strcpy(this->ime, ime);
        this->br_pobedi = br_pobedi;
        this->br_porazi = br_porazi;
    }

    ~Ekipa(){}

    void pecati(){
        cout<<ime<<" "<<br_pobedi<<" "<<br_porazi;
    }
};

class FudbalskaEkipa : public Ekipa{
private:
    int crveniKartoni;
    int zoltiKartoni;
    int nereseno;
public:
    FudbalskaEkipa(char ime[]="", int br_pobedi=0, int br_porazi=0, int crveniKartoni=0, int zoltiKartoni=0, int nereseno=0)
    : Ekipa(ime, br_pobedi, br_porazi){
        this->crveniKartoni = crveniKartoni;
        this->zoltiKartoni = zoltiKartoni;
        this->nereseno = nereseno;
    }

    ~FudbalskaEkipa(){}

    void pecati(){
        Ekipa::pecati();
        cout<<" "<<nereseno<<" "<<br_pobedi*3 + nereseno*1<<endl;
    }
};

int main(){
    Ekipa e("ime", 2, 5);
    e.pecati();
    cout<<endl;
    FudbalskaEkipa f("ime", 2, 3, 1, 4, 1);
    f.pecati();
    return 0;
}
