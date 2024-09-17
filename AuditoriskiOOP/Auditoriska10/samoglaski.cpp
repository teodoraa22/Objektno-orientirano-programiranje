//
// Created by Teodora on 03.6.2024.
//
#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>          //bibloteka za rabota so datoteki
using namespace std;

int main(){
    ifstream dat("C:\\Users\\Teodora\\CLionProjects\\SP_2023\\OOP\\AuditoriskiOOP\\Auditoriska10\\input.txt");
    if(!dat.is_open()){
        cout<<"Ne mozam da ja otvoram datotekata."<<endl;
        return -1;
    }
    char c;    //current character
    int samoglaski = 0, samoglaski_red = 0;
    int red = 0;
    while (dat.get(c)){       //citanje na file-ot karakter po karakter i kje vrti se dodeka ima karakter vo nego
        c = tolower(c);
        if(c == 'a' || c=='e' || c=='i' || c=='o' || c=='u'){
            samoglaski++;
            samoglaski_red++;
        }
        if(c=='\n'){
            if(samoglaski_red>= 10){
                red++;
            }
            samoglaski_red = 0;
        }
    }
    if(samoglaski_red>= 10){
        red++;
    }
    cout<<"Vkupno "<<red<<" reda imaat povekje od 10 samoglaski."<<endl;
    cout<<"Vo datotekata ima vkupno "<<samoglaski<<" samoglaski."<<endl;
    return 0;
}