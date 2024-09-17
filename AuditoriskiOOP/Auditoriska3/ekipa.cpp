//
// Created by Teodora on 20.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Ekipa{
private:
    char ime[20];
    int godina;
    char grad[20];
public:
    Ekipa(char ime[], int godina, char grad[]){
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->grad, grad);
    }
    Ekipa(){}
    char *get_ime(){
        return ime;
    }
    ~Ekipa(){}
};

class Natprevar{
private:
    Ekipa domakin;
    Ekipa gostin;
    int goloviDomakin;
    int goloviGostin;
public:
    Natprevar(Ekipa domakin, Ekipa gostin, int goloviDomakin, int goloviGostin){
        this->domakin = domakin;
        this->gostin = gostin;
        this->goloviDomakin = goloviDomakin;
        this->goloviGostin = goloviGostin;
    }
    Natprevar(){}
    void set_se(Ekipa domakin, Ekipa gostin, int goloviDomakin, int goloviGostin){
        this->domakin = domakin;
        this->gostin = gostin;
        this->goloviDomakin = goloviDomakin;
        this->goloviGostin = goloviGostin;
    }
    Ekipa get_domakin(){
        return domakin;
    }
    Ekipa get_gostin(){
        return gostin;
    }
    int getGoloviDomakin(){
        return goloviDomakin;
    }
    int getGoloviGostin(){
        return goloviGostin;
    }
    ~Natprevar(){}
};

bool revans(Natprevar n1, Natprevar n2){
    if((strcmp(n1.get_domakin().get_ime(), n2.get_gostin().get_ime()) == 0 &&
        strcmp(n1.get_gostin().get_ime(), n2.get_domakin().get_ime()) == 0)){
        return true;
    }
    return false;
}

Ekipa duel(Natprevar n1, Natprevar n2){
    if(revans(n1, n2)){
        int t1_golovi = n1.getGoloviDomakin() + n2.getGoloviGostin();
        int t2_golovi = n2.getGoloviDomakin() + n1.getGoloviGostin();
        if(t1_golovi > t2_golovi){
            return n1.get_domakin();
        }else if(t1_golovi < t2_golovi){
            return n1.get_gostin();
        }else if(n1.getGoloviGostin() > n2.getGoloviGostin()){
            return n1.get_gostin();
        }else if(n1.getGoloviGostin() < n2.getGoloviGostin()){
            return n1.get_domakin();
        }else{
            cout<<"Ist broj poeni"<<endl;
        }
    }else{
        cout<<"Ne se sovpagjaat"<<endl;
    }
}

int main(){
    Natprevar natprevar[100];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char ime[20], grad[20];
        int godina, goloviDomakin, goloviGostin;
        cin>>ime>>godina>>grad>>goloviDomakin>>goloviGostin;
        Ekipa e(ime, godina, grad);
        natprevar[i].set_se(e,e,goloviDomakin,goloviGostin);
    }
    cout << "Pobednik: " << duel(natprevar[0], natprevar[1]).get_ime() << endl;
    return 0;
}