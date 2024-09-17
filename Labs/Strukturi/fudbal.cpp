//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
using namespace std;

struct FudbalskiIgrac{
    char ime_igrac[30];
    int br_dres;
    int gol;
};

struct FudbalskiTim{
    char ime_tim[30];
    FudbalskiIgrac igrac[11];
    int vkupno_gol = 0;
    
    void read(){
        cin>>ime_tim;
        for (int i = 0; i < 11; ++i) {
            cin>>igrac[i].ime_igrac>>igrac[i].br_dres>>igrac[i].gol;
            vkupno_gol += igrac[i].gol;
        }
    }
};

void best_team(FudbalskiTim f[], int n){
    FudbalskiTim max = f[0];
    for (int i = 0; i < n; ++i) {
        if(f[i].vkupno_gol > max.vkupno_gol){
            max = f[i];
        }
    }
    cout<<"Najdobar tim e: "<<max.ime_tim;
}

int main(){
    FudbalskiTim t[30];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        t[i].read();
    }
    best_team(t, n);
    return 0;
}