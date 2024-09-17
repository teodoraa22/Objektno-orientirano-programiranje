//
// Created by Teodora on 03.6.2024.
//
#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>
using namespace std;

bool samoglaska(char c){
    switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

int main(){
    ifstream input("C:\\Users\\Teodora\\CLionProjects\\SP_2023\\OOP\\AuditoriskiOOP\\Auditoriska10\\input.txt");
    ofstream output("C:\\Users\\Teodora\\CLionProjects\\SP_2023\\OOP\\AuditoriskiOOP\\Auditoriska10\\output.txt");
    if(!input.is_open()){
        cout<<"Datotekata ne e otvorena!"<<endl;
        return -1;
    }
    string line;
    int red=0, vkupno=0;
    while(getline(input,line)){
        int samoglaski = 0;
        for (int i = 0; i < line.length(); ++i) {
            if(samoglaska(line[i])){
                samoglaski++;
                vkupno++;
            }
        }
        if(samoglaski>=10){
            red++;
        }
    }
    output<<"Vkupno "<<red<<" reda imaat povekje od 10 samoglaski."<<endl;
    output<<"Vo datotekata ima vkupno "<<vkupno<<" samoglaski."<<endl;
    return 0;
}