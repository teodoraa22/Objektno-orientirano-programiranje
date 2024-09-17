//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
using namespace std;

struct Engine{
    int konjskaSila;
    int moment;

    void read(){
        cin>>konjskaSila>>moment;
    }
};

struct Car{
    char ime_na_proizvoditel[50];
    int godina;
    Engine motor;

    void read(){
        cin>>ime_na_proizvoditel>>godina;
        motor.read();
    }

    void print(){
        cout<<"Manufacturer: "<<ime_na_proizvoditel<<endl;
        cout<<"Horsepower: "<<motor.konjskaSila<<endl;
        cout<<"Torque: "<<motor.moment<<endl;
    }
};

void printCars(Car koli[], int n){
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (koli[i].motor.konjskaSila > koli[j].motor.konjskaSila){
                swap(koli[i], koli[j]);
            }
        }
    }
    if(koli[0].motor.moment > koli[1].motor.moment){
        koli[0].print();
    }else{
        koli[1].print();
    }
}

int main(){
    Car koli[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        koli[i].read();
    }
    printCars(koli, n);
    return 0;
}