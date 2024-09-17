//
// Created by Teodora on 15.5.2024.
//
/*
Numbers Problem 4 (2 / 7)
Да се дефинира апстрктна класа Number со следните чисто виртуелни методи:

double doubleValue() -ја враќа децималната вредност на даден број
int intValue()- ја враќа целобројната вредност на даден број
void print() - печати информации за бројот. (1 поен)
Од оваа класа да се изведат две класи:

Integer (во која што се чува еден број од тип int)
Double (во која што се чува еден број од тип double) (1 поен).
За двете изведени класи да се имплементираaт соодветен конструктори, како и да се препокријат методите од основната класа. (1 поени)

Да се преоптовари операторот == којшто ќе споредува два броеви според нивната вредност (објекти од класа Number) (1 поен)

Дополнително да се дефинира класа Numbers во која што ќе се чуваат:

динамички алоцирана низа од покажувачи кон објекти од класата Number
број на елементи во низата од покажувачи
За класата да се имплементира соодветен конструктор (default) , како и: (1 поени)

операторот += за додавање на броеви во низата од броеви (1 поен)
Бројот се додава ако и само ако сите броеви што се веќе додадени во низата се различни од него
функција void statistics() која што печати информации за броевите во низата: (2 поени)
Count of numbers: [број на броеви во низата

Sum of all numbers: [сума на сите броеви во низата]

Count of integer numbers: [број на цели броеви (Integer)]

Sum of integer numbers: [сума на сите цели броеви (Integer)]

Count of double numbers: [број на децимални броеви (Double)]

Sum of double numbers: [сума на сите децимални броеви (Double)]

функција void integersLessThan (Integer n) која што ги печати сите цели броеви помали од бројот n (1 поен)
функција void doublesBiggerThan (Double n) која што ги печати сите децимални броеви поголеми од бројот n (1 поен)

100%
*/
#include<iostream>
#include<cstring>
using namespace std;

class Number{
public:
    virtual double doubleValue() = 0;

    virtual int intValue() = 0;

    virtual void print() = 0;

    bool operator==(Number &n){
        return (this->doubleValue() == n.doubleValue());
    }
};

class Integer : public Number{
private:
    int broj;
public:
    Integer(int broj = 0){
        this->broj = broj;
    }

    double doubleValue(){
        return double(broj);
    }

    int intValue(){
        return broj;
    }

    void print(){
        cout<<broj<<endl;
    }
};

class Double : public Number{
private:
    double broj;
public:
    Double(double broj = 0){
        this->broj = broj;
    }

    double doubleValue(){
        return broj;
    }

    int intValue(){
        return int(broj);
    }

    void print(){
        cout<<broj<<endl;
    }
};

class Numbers{
private:
    Number **niza;
    int brojElemnti;
public:
    Numbers(){
        niza = new Number*[brojElemnti];
        brojElemnti = 0;
    }

    Numbers(const Numbers &num){
        brojElemnti = num.brojElemnti;
        niza = new Number*[num.brojElemnti];
        for (int i = 0; i < num.brojElemnti; ++i) {
            niza[i] = num.niza[i];
        }
    }

    Numbers &operator=(const Numbers &num){
        if(this != &num){
            delete [] niza;
            brojElemnti = num.brojElemnti;
            niza = new Number*[num.brojElemnti];
            for (int i = 0; i < num.brojElemnti; ++i) {
                niza[i] = num.niza[i];
            }
        }
        return *this;
    }

    ~Numbers(){
        delete [] niza;
    }

    Numbers &operator+=(Number *num){
        bool add = true;
        for (int i = 0; i < brojElemnti; ++i) {
            if(*niza[i] == *num){
                add = false;
            }
        }
        if(add){
            Number **nova = new Number *[brojElemnti+1];
            for (int i = 0; i < brojElemnti; ++i) {
                nova[i] = niza[i];
            }
            nova[brojElemnti++] = num;
            delete [] niza;
            niza = nova;
        }
        return *this;
    }

    void statistics(){
        double suma = 0;
        int celiBroevi = 0;
        int sumaNaCeliBroevi = 0;
        int decimalniBroevi = 0;
        double sumaNaDecimalniBroevi =0;

        for (int i = 0; i < brojElemnti; ++i) {
            suma += niza[i]->doubleValue();
        }

        for (int i = 0; i < brojElemnti; ++i) {
            if(dynamic_cast<Integer*>(niza[i])){
                celiBroevi++;
                sumaNaCeliBroevi += niza[i]->intValue();
            }
        }

        for (int i = 0; i < brojElemnti; ++i) {
            if(dynamic_cast<Double*>(niza[i])){
                decimalniBroevi++;
                sumaNaDecimalniBroevi += niza[i]->doubleValue();
            }
        }
        cout<<"Count of numbers: "<<brojElemnti<<endl;
        cout<<"Sum of all numbers: "<<suma<<endl;
        cout<<"Count of integer numbers: "<<celiBroevi<<endl;
        cout<<"Sum of integer numbers: "<<sumaNaCeliBroevi<<endl;
        cout<<"Count of double numbers: "<<decimalniBroevi<<endl;
        cout<<"Sum of double numbers: "<<sumaNaDecimalniBroevi<<endl;
    }

    void integersLessThan (Integer n){
        bool flag = true;
        for (int i = 0; i < brojElemnti; ++i) {
            if(dynamic_cast<Integer*>(niza[i])){
                if(niza[i]->intValue() < n.intValue()){
                    flag = false;
                    cout<<"Integer: "<<niza[i]->intValue()<<endl;
                }
            }
        }
        if(flag){
            cout<<"Nema integer pomal od broj na elementi. "<<endl;
        }
    }

    void doublesBiggerThan (Double n){
        bool flag = true;
        for (int i = 0; i < brojElemnti; ++i) {
            if (dynamic_cast<Double*>(niza[i])){}
            if(niza[i]->doubleValue() > n.doubleValue()){
                flag = false;
                cout<<"Double: "<<niza[i]->doubleValue()<<endl;
            }
        }
        if(flag){
            cout<<"Nema double pogolem od broj na elementi. "<<endl;
        }
    }
};

int main(){
    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));
    return 0;
}