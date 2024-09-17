//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
using namespace std;

struct Transakcija{
    int id_broj;
    int suma;
    int provizija;
    bool karticka;

    void read(){
        cin>>id_broj>>suma>>provizija>>karticka;
    }
};

int main(){
    Transakcija t[10];
    int n;
    cin>>n;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        t[i].read();
        if(t[i].karticka == 1){
            flag = true;
            cout<<t[i].id_broj<<" "<<t[i].suma + t[i].provizija<<endl;
        }
    }
    if(flag == false){
        cout<<"No credit card transaction";
    }
    return 0;
}