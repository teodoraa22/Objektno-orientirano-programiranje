//
// Created by Teodora on 18.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Country{
private:
    char name[100];
    char capital[100];
    float area;
    float population;
public:
    Country(char n[], char c[], float a, float p){
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }
    Country(){}
    ~Country(){}
    void set_se(char n[], char c[], float a, float p){
        strcpy(name, n);
        strcpy(capital, c);
        area = a;
        population = p;
    }
    float get_povrsina(){
        return area;
    }
    void display(){
        cout<<"Country: "<<name<<endl;
        cout<<"Capital: "<<capital<<endl;
        cout<<"Area: "<<area<<endl;
        cout<<"Population: "<<population<<endl;
    }
};

void sortCountries(Country country[], int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if(country[j].get_povrsina() < country[j+1].get_povrsina()){
                Country temp = country[j];
                country[j] = country[j+1];
                country[j+1] = temp;
            }
        }
    }
}

int main(){
    Country d("Guyana", "Georgetown", 214, 0.8);
    Country drzava[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[100], gl_grad[100];
        float povrsina, populacija;
        cin>>ime>>gl_grad>>povrsina>>populacija;
        drzava[i].set_se(ime, gl_grad, povrsina, populacija);
    }
    sortCountries(drzava, n);
    for (int i = 0; i < n; ++i) {
        drzava[i].display();
    }
    return 0;
}