//
// Created by Teodora on 04.6.2024.
//
#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
private:
    char ime[50];
    int godina;
    char poteklo[50];
public:
    Delo(char *ime="", int godina=0, char *poteklo=""){
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->poteklo, poteklo);
    }

    bool operator==(Delo &other){
        return strcmp(ime, other.ime) == 0;
    }

    int getGodina(){
        return godina;
    }

    char *getPoteklo(){
        return poteklo;
    }

    char *getIme(){
        return ime;
    }
};

class Pretstava{
private:
    Delo d;
    int karti;
    char datum[15];
public:
    Pretstava(Delo d=0, int karti=0, char *datum=""){
        this->d = d;
        this->karti = karti;
        strcpy(this->datum, datum);
    }

    int cena(){
        int n, m;
        if(d.getGodina() > 1900){
            m = 50;
        }else if(d.getGodina() > 1800){
            m = 75;
        }else{
            m = 100;
        }
        if(strcmp(d.getPoteklo(), "Italija") == 0){
            n = 100;
        }else if(strcmp(d.getPoteklo(), " Rusija") == 0){
            n = 150;
        }else{
            n = 80;
        }
        return m + n;
    }

    Delo getDelo(){
        return d;
    }

    friend int prihod(Pretstava **pretstavi, int n);
    friend int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo d);
};

class Balet : public Pretstava{
private:
    static int cena_balet;
public:
    Balet(Delo d=0, int karti=0, char *datum="")
    : Pretstava(d, karti, datum){}

    static void setCenaBalet(int n){
        cena_balet = n;
    }
};

int Balet::cena_balet = 150;

class Opera : public Pretstava{
public:
    Opera(Delo d=0, int karti=0, char *datum="")
    : Pretstava(d, karti, datum){}
};

int prihod(Pretstava **pretstavi, int n){
    int vkupno = 0;
    for (int i = 0; i < n; ++i) {
        vkupno += pretstavi[i]->cena() + pretstavi[i]->karti;
    }
    return vkupno;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo d){
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if(pretstavi[i]->d == d){
            count++;
        }
    }
    return count;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}