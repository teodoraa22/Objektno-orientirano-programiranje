//
// Created by Teodora on 04.6.2024.
//
#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

//место за вашиот код
class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena;
public:
    Oglas(char *naslov="", char *kategorija="", char *opis="", double cena=0){
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }

    bool operator>(Oglas &other){
        return cena > other.cena;
    }

    friend ostream &operator<<(ostream &out, Oglas &o){
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        return out;
    }

    int getCena(){
        return cena;
    }

    char *getKategorija(){
        return kategorija;
    }
};

class NegativnaVrednost{
public:
    void message(){
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglasnik{
private:
    char oglasnik[20];
    Oglas *oglas;
    int n;       //broj na oglasi
public:
    Oglasnik(char *oglasnik=""){
        strcpy(this->oglasnik, oglasnik);
        n = 0;
        oglas = new Oglas[n];
    }

    Oglasnik(const Oglasnik &o){
        strcpy(this->oglasnik, o.oglasnik);
        n = o.n;
        oglas = new Oglas[o.n];
        for (int i = 0; i < o.n; ++i) {
            this->oglas[i] = o.oglas[i];
        }
    }

    Oglasnik operator=(const Oglasnik &o){
        if(this != &o){
            delete [] oglas;
            strcpy(this->oglasnik, o.oglasnik);
            n = o.n;
            oglas = new Oglas[o.n];
            for (int i = 0; i < o.n; ++i) {
                this->oglas[i] = o.oglas[i];
            }
        }
        return *this;
    }

    ~Oglasnik(){
        delete [] oglas;
    }

    Oglasnik operator+=(Oglas &o){
        if(o.getCena() < 0){
            throw NegativnaVrednost();
        }
        Oglas *temp = new Oglas[n+1];
        for (int i = 0; i < n; ++i) {
            temp[i] = oglas[i];
        }
        temp[n++] = o;
        delete [] oglas;
        oglas = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Oglasnik &o){
        out<<o.oglasnik<<endl;
        for (int i = 0; i < o.n; ++i) {
            out<<o.oglas[i]<<endl;
        }
        return out;
    }

    void najniskaCena() {
        Oglas najeftin = oglas[0];
        for (int i = 0; i < n; ++i) {
            if(oglas[i].getCena() < najeftin.getCena()){
                najeftin = oglas[i];
            }
        }
        cout<<najeftin<<endl;
    }

    void oglasiOdKategorija(char *k) {
        for (int i = 0; i < n; ++i) {
            if(strcmp(oglas[i].getKategorija(), k) == 0){
                cout<<oglas[i]<<endl;
            }
        }
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try {
                Oglas o(naslov, kategorija, opis, cena);
                ogl += o;
            }catch (NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
