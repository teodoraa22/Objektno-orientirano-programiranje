//
// Created by Teodora on 03.6.2024.
//
#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class FudbalskaEkipa{
protected:
    char ime[100];
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *trener="", int golovi[10] = 0, char *ime=""){
        strcpy(this->trener, trener);
        for (int i = 0; i < 10; ++i) {
            this->golovi[i] = golovi[i];
        }
        strcpy(this->ime, ime);
    }

    virtual int uspeh() = 0;

    friend ostream &operator<<(ostream &o, FudbalskaEkipa &f){
        o<<f.ime<<"\n"<<f.trener<<"\n"<<f.uspeh()<<"\n";
        return o;
    }

    bool operator>(FudbalskaEkipa &other){
        return uspeh() > other.uspeh();
    }

    FudbalskaEkipa& operator+=(int g){
        for (int i = 0; i < 9; ++i) {
            golovi[i] = golovi[i + 1];
        }
        golovi[9] = g;
        return *this;
    }

};

class Klub : public FudbalskaEkipa{
private:
    int tituli;
public:
    Klub(char *trener="", int golovi[10] = 0, char *ime="", int tituli=0)
    : FudbalskaEkipa(trener, golovi, ime){
        this->tituli = tituli;
    }

    int uspeh() override{
        int zbir = 0;
        for (int i = 0; i < 10; ++i) {
            zbir += golovi[i];
        }
        return zbir*3 + tituli*1000;
    }

    friend ostream &operator<<(ostream &o, Klub &k){
        o<<k.ime<<"\n"<<k.trener<<"\n"<<k.uspeh()<<"\n";
        return o;
    }
};

class Reprezentacija : public FudbalskaEkipa{
private:
    int natprevari;
public:
    Reprezentacija(char *trener="", int golovi[10] = 0, char *ime="", int natprevari=0)
    : FudbalskaEkipa(trener, golovi, ime){
        strcpy(this->ime, ime);
        this->natprevari = natprevari;
    }

    int uspeh() override{
        int zbir = 0;
        for (int i = 0; i < 10; ++i) {
            zbir += golovi[i];
        }
        return zbir*3 + natprevari*50;
    }

    friend ostream &operator<<(ostream &o, Reprezentacija &r){
        o<<r.ime<<"\n"<<r.trener<<"\n"<<r.uspeh()<<"\n";
        return o;
    }
};

void najdobarTrener(FudbalskaEkipa **ekipi, int n) {
    FudbalskaEkipa *najdobar = ekipi[0];
    for (int i = 0; i < n; ++i) {
        if(ekipi[i]->uspeh() > najdobar->uspeh()){
            najdobar = ekipi[i];
        }
    }
    cout<<*najdobar<<endl;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}