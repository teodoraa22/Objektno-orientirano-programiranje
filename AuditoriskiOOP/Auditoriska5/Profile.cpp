//
// Created by Teodora on 29.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Profile{
private:
    char ime[15];
    int brPrijateli;
    static int maxPrijateli;
    int godinaRagjanje;
public:
    Profile(char *ime="", int brPrijateli=0, int godinaRagjanje=0){
        strcpy(this->ime, ime);
        this->brPrijateli = brPrijateli;
        this->godinaRagjanje = godinaRagjanje;
    }
    Profile(const Profile &p){
        strcpy(this->ime, p.ime);
        this->brPrijateli = p.brPrijateli;
        this->godinaRagjanje = p.godinaRagjanje;
    }
    ~Profile(){}

    //p.sporedi(p1)
    bool sporedi(Profile p){
        if(brPrijateli == p.brPrijateli){
            return true;
        }else{
            return false;
        }
    }

    //p==p1
    bool operator==(Profile p){
        if(brPrijateli == p.brPrijateli){
            return true;
        }else{
            return false;
        }
    }

    //p==15
    bool operator==(int broj){
        if(brPrijateli == broj){
            return true;
        }else{
            return false;
        }
    }

    //15==p
    friend bool operator==(int broj, Profile p); //friend = pristapuvam do privatnite clenovi nadvor od klasata

    //p>p1
    bool operator>(Profile p){
        if(godinaRagjanje > p.godinaRagjanje){
            return true;
        }else{
            return false;
        }
    }

    //p!=p1
    bool operator!=(Profile p){
        if(godinaRagjanje != p.godinaRagjanje){
            return true;
        }else{
            return false;
        }
    }

    //p1=p++
    Profile operator++(int){    //post
        Profile kopija = *this;
        brPrijateli+=1;
        return kopija;
    }

    Profile &operator++(){
        brPrijateli+=1;
        return *this;
    }

    //p+=10
    void operator+=(int broj){
        brPrijateli+=broj;
    }

    //cout<<p
    friend ostream &operator<<(ostream &output, Profile &p);

    //cin>>p
    friend istream &operator>>(istream &input, Profile &p);
};

class SocialMedia{
private:
    char ime[15];
    Profile *niza;
    int n; //broj na profili
public:
    SocialMedia(char  *ime=""){
        strcpy(this->ime, ime);
        n=0;
        niza = new Profile[n];
    }

    //s+=p
    SocialMedia operator+=(Profile p){
        Profile *pomosna = new Profile[n+1];
        for (int i = 0; i < n; ++i) {
            pomosna[i] = niza[i];
        }
        pomosna[n] = p;
        delete [] niza;
        niza = pomosna;
        n++;
        return *this;
    }
    ~SocialMedia(){}
};

int Profile::maxPrijateli = 500;

//15==p
bool operator==(int broj, Profile p){
    if(broj == p.brPrijateli){
        return true;
    }else{
        return false;
    }
}

//cout<<p
ostream &operator<<(ostream &output, Profile &p){
    output<<p.ime<<" "<<p.brPrijateli<<" "<<p.godinaRagjanje<<endl;
    return output;
}

//cin>>p
istream &operator>>(istream &input, Profile &p){
    input>>p.ime>>p.brPrijateli>>p.godinaRagjanje;
    return input;
}

int main(){
    Profile p("Ime", 15, 1950);
    Profile p1("Ime2", 15, 1955);
    p.sporedi(p1);
    cout<<(p==p1)<<endl;//p.sporedi(p1)
    p==15;
    15==p;
    p>p1;
    p!=p1;
    p1=p++;
    p+=10;
    cout<<p;
    cin>>p;
    cout<<p;
    SocialMedia s("Mreza");
    s+=p;
}