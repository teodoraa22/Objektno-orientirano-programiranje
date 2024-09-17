//
// Created by Teodora on 26.4.2024.
//
#include <iostream>
#include <string>
using namespace std;

class Lekar{
protected:
    int faksimil;
    string ime;
    string prezime;
    double pocetna_plata;
public:
    Lekar(int faksimil=0, string ime="", string prezime="", float pocetna_plata=0){
        this->faksimil = faksimil;
        this->ime = ime;
        this->prezime = prezime;
        this->pocetna_plata = pocetna_plata;
    }

    void pecati(){
        cout<<faksimil<<": "<<ime<<" "<<prezime;
    }

    double plata(){
        return pocetna_plata;
    }
};

class MaticenLekar : public Lekar{
private:
    int pacienti;
    double *kotizacii;
public:
    MaticenLekar(Lekar l, int pacienti=0, double *kotizacii=0)
    : Lekar(l){
        this->pacienti = pacienti;
        this->kotizacii = new double[pacienti];
        for (int i = 0; i < pacienti; ++i) {
            this->kotizacii[i] = kotizacii[i];
        }
    }

    MaticenLekar(){}

    MaticenLekar &operator=(const MaticenLekar &m){
        if(this!=&m){
            delete [] kotizacii;
            this->faksimil = m.faksimil;
            this->ime = m.ime;
            this->prezime = m.prezime;
            this->pocetna_plata = m.pocetna_plata;
            this->pacienti = m.pacienti;
            this->kotizacii = new double[m.pacienti];
            for (int i = 0; i < m.pacienti; ++i) {
                this->kotizacii[i] = m.kotizacii[i];
            }
        }
        return *this;
    }

    ~MaticenLekar(){
        delete [] kotizacii;
    }

    double prosek(){
        double suma=0;
        for (int i = 0; i < pacienti; ++i) {
            suma += kotizacii[i];
        }
        return (double)suma/pacienti;
    }

    double plata(){
        return pocetna_plata + prosek()/100.0*30;
    }

    void pecati(){
        Lekar::pecati();
        cout<<" "<<prosek()<<endl;
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}