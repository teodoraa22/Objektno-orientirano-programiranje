//
// Created by Teodora on 05.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

struct Student{
    char ime[50];
    char prezime[50];
    int index;
    int poeni;

    void print(){
        cout<<ime<<" "<<prezime<<" "<<index<<" "<<poeni<<endl;
    }
};

void golemaPocetnaBukva(char str[]){
    str[0] = toupper(str[0]);
    for (int i = 1; i < strlen(str); ++i) {
        str[i] = tolower(str[i]);
    }
}

void sort(Student niza[], int n){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1-i; ++j) {
            if(niza[j].poeni < niza[j+1].poeni){
                Student temp =  niza[j];
                niza[j] = niza[j+1];
                niza[j+1] = temp;
            }
        }
    }
}

int main(){
    Student niza[100];
    int n;
    cin>>n;

    for (int i = 0; i < n; ++i) {
        cin>>niza[i].ime;
        golemaPocetnaBukva(niza[i].ime);
        cin>>niza[i].prezime;
        golemaPocetnaBukva(niza[i].prezime);
        cin>>niza[i].index;
        int p;
        for (int j = 0; j < 4; ++j) {
            cin>>p;
            niza[i].poeni += p;
        }
    }

    sort(niza, n);

    for (int i = 0; i < n; ++i) {
        niza[i].print();
    }
    return 0;
}