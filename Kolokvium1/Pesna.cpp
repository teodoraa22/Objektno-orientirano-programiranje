//
// Created by Teodora on 04.4.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

enum tip{
    pop, rap, rok   //0, 1, 2
};

class Pesna{
private:
    char *ime;
    int min;
    tip t;
public:
  Pesna(char *ime="", int min=0, tip t=pop){
      this->ime = new char[strlen(ime) + 1];
      strcpy(this->ime, ime);
      this->min = min;
      this->t = t;
  }

  Pesna(const Pesna &p){
      this->ime = new char[strlen(p.ime) + 1];
      strcpy(this->ime, p.ime);
      this->min = p.min;
      this->t = p.t;
  }

  Pesna &operator==(Pesna &p){
      if(this != &p){
          delete [] ime;
          this->ime = new char[strlen(p.ime) + 1];
          strcpy(this->ime, p.ime);
          this->min = p.min;
          this->t = p.t;
      }
      return *this;
  }

  ~Pesna(){}

  void pecati(){
      cout<<"\""<<ime<<"\"-"<<min<<"min"<<endl;
  }

  int getMin(){
      return min;
  }

  tip getTip(){
      return t;
  }
};

class CD{
private:
    Pesna niza[10]; // niza od pesni
    int brojPesni;
    int maxMin;    // maksimalno vremetraenje
public:
    CD(int maxMin){
        brojPesni = 0;
        this->maxMin = maxMin;
    }

    ~CD(){}

    bool dodadiPesna (Pesna p){
        if(brojPesni >= 10 || (vreme() + p.getMin()) > maxMin){
            return false;
        }
        niza[brojPesni++] = p;
        return true;
    }

    void pecatiPesniPoTip(tip t){
        for (int i = 0; i < brojPesni; ++i) {
            if(niza[i].getTip() == t){
                niza[i].pecati();
            }
        }
    }

    int getBroj(){
        return brojPesni;
    }

    Pesna getPesna(int i){
        return niza[i];
    }

    int vreme(){
        int vreme = 0;
        for (int i = 0; i < brojPesni; ++i) {
            vreme += niza[i].getMin();
        }
        return vreme;
    }

};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}