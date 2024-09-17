//
// Created by Teodora on 20.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class MobilePhone{
private:
    char model[20];
    int br_model;
    int godina;
public:
    MobilePhone(char m[], int br, int g){
        strcpy(model, m);
        br_model = br;
        godina = g;
    }
    MobilePhone(){}
    ~MobilePhone(){}
    void pecati(){
        cout<<model<<" "<<br_model<<" release year: "<<godina<<endl;
    }
};

class Owner{
private:
    char ime[20];
    char prezime[20];
    MobilePhone mobilePhone;
public:
    Owner(char i[], char p[], MobilePhone m){
        strcpy(ime, i);
        strcpy(prezime, p);
        mobilePhone = m;
    }
    Owner(){}
    ~Owner(){}
    void pecati(){
        cout<<ime<<" "<<prezime<<" has a mobile phone: "<<endl;
        mobilePhone.pecati();
    }
};

int main(){
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.pecati();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.pecati();
    }
    return 0;
}