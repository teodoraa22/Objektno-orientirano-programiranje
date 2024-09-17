//
// Created by Teodora on 15.5.2024.
//Apstrakna klasa ima cisto virtuelna funkcija
//Od apstrakna klasa ne moze da se kreira objekt, tuku samo pokazuvaci ili referenci
// koi pokazuvaat kon izvedenite klasi od taa klasa

#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class GeometriskoTelo{
protected:
    double visina;
public:
    GeometriskoTelo(double visina = 0){
        this->visina = visina;
    }

    virtual void pecati(){
        cout<<visina<<endl;
    }

    //cisto virtuelna funkcija
    virtual double volumen() = 0;

    double getVisina() const{
        return visina;
    }
};

class Cilinder : public GeometriskoTelo{
private:
    double radius;
public:
    Cilinder(double visina = 0, double radius = 0)
    : GeometriskoTelo(visina){
        this->radius = radius;
    }

    void pecati(){
        cout<<"Cilinder so visina: ";
        GeometriskoTelo::pecati();
        cout<<"Radius: "<<radius<<endl;
    }

    double volumen(){
        return M_PI*radius*radius*getVisina();
    }

    double getRadius(){
        return radius;
    }
};

class Konus : public GeometriskoTelo{
private:
    double radius;
public:
    Konus(double visina = 0, double radius = 0)
            : GeometriskoTelo(visina){
        this->radius = radius;
    }

    void pecati(){
        cout<<"Konus so visina: ";
        GeometriskoTelo::pecati();
        cout<<"Radius: "<<radius<<endl;
    }

    double volumen(){
        return M_PI*radius*radius*getVisina() / 3.0;
    }

    double getRadius(){
        return radius;
    }
};

class Kvadar : public GeometriskoTelo{
private:
    double a;
    double b;
public:
    Kvadar(double visina = 0, double a = 0, double b = 0)
    : GeometriskoTelo(visina){
        this->a = a;
        this->b = b;
    }

    void pecati(){
        cout<<"Kvadar so visina: ";
        GeometriskoTelo::pecati();
        cout<<"Starana a: "<<a<<", Strana b: "<<b<<endl;
    }

    double volumen(){
        return a*b*getVisina();
    }
};

void teloSoNajgolemVolumen(GeometriskoTelo *niza[], int n){
    int najgolemVolumen = 0;
    int index = 0;
    for (int i = 0; i < n; ++i) {
        if(niza[i]->volumen() > najgolemVolumen){
            najgolemVolumen = niza[i]->volumen();
            index = i;
        }
    }
    cout<<"Najgolem volumen: "<<endl;
    niza[index]->pecati();
}

double getRadius(GeometriskoTelo *g){
    Cilinder *pok = dynamic_cast<Cilinder*>(g);
    if(pok!=0){
        return pok->getRadius();
    }
    Konus *pok1 = dynamic_cast<Konus*>(g);
    if(pok1!=0){
        return pok1->getRadius();
    }
    return -1;
}

int main(){
    GeometriskoTelo** mnozestvoTela; //динамички алоцирано поле од покажувачи кон GeomTelo
    int n;
    cin>>n; //број на тела во множеството
    mnozestvoTela = new GeometriskoTelo *[n]; //се алоцира меморија за полето од покажувачи
    for (int i = 0 ; i < n ; i++){
        int r,a,b,h,type;
        cout<<"Kakvo telo: 1-cilinder 2-konus 3-kvadar "<<endl;
        cin >> type;
        if (type==1)
        { //ако корисникот внесува цилиндер
            cin >> h >> r;
            mnozestvoTela[i]= new Cilinder(h,r);
        }
        if (type==2)
        { //ако корисникот внесува конус
            cin >> h >> r;
            mnozestvoTela[i]= new Konus(h,r);
        }
        if (type==3)
        { //ако корисникот внесува квадар
            cin >> h >> a >> b;
            mnozestvoTela[i]= new Kvadar(h, a, b);
        }
    }
    //барање 1
    teloSoNajgolemVolumen(mnozestvoTela,n);
    //барање 2
    int brojac=0;
    for (int i = 0 ; i < n ; i++)
        if (getRadius(mnozestvoTela[i]) == -1)
            brojac++;
    cout<<"Brojot na tela koi nemaat osnova krug e "<<brojac;
    return 0;
}
