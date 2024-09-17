//
// Created by Teodora on 09.4.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Flight{
private:
    char poletuvanje[50];
    char sletuvanje[50];
    float vremetraenje;
    float cena;
public:
    Flight(char *poletuvanje="", char *sletuvanje="", float vremetraenje=0, float cena=0){
        strcpy(this->poletuvanje, poletuvanje);
        strcpy(this->sletuvanje, sletuvanje);
        this->vremetraenje = vremetraenje;
        this->cena = cena;
    }
    ~Flight(){}
    void printDuration(){
        cout<<(int)vremetraenje<<"h:"<<(vremetraenje-(int)vremetraenje)*60<<"min";
    }
    void printFlight(){
        cout<<poletuvanje<<" -> ";
        printDuration();
        cout<<" -> "<<sletuvanje<<endl;
    }

    char *get_poletuvanje(){
        return poletuvanje;
    }

    char *get_sletuvanje(){
        return sletuvanje;
    }
};

class Airline{
private:
    char ime[50];
    Flight *letovi;
    int n;    //broj na letovi
public:
    Airline(char *ime=""){
        strcpy(this->ime, ime);
        n = 0;
        letovi = new Flight[n];
    }
    Airline(const Airline &a){
        strcpy(this->ime, a.ime);
        n = a.n;
        letovi = new Flight[a.n];
        for (int i = 0; i < n; ++i) {
            letovi[i] = a.letovi[i];
        }
    }
    Airline &operator=(Airline &a){
        if(this != &a){
            delete [] letovi;
            strcpy(this->ime, a.ime);
            n = a.n;
            letovi = new Flight[a.n];
            for (int i = 0; i < n; ++i) {
                letovi[i] = a.letovi[i];
            }
        }
        return *this;
    }
    ~Airline(){
        delete [] letovi;
    }
    bool operator==(Flight f){
        for (int i = 0; i < n; ++i) {
            if(strcmp(letovi[i].get_poletuvanje(), f.get_poletuvanje())==0 && strcmp(letovi[i].get_sletuvanje(), f.get_sletuvanje()) == 0){
                return true;
            }
            return false;
        }
    }
    void addFlight(Flight f){
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            if(strcmp(letovi[i].get_poletuvanje(), f.get_poletuvanje())==0 && strcmp(letovi[i].get_sletuvanje(), f.get_sletuvanje()) == 0){
                flag = true;
                return;
            }
        }

        //доколку не постои го додаваме новиот лет
        if(!flag){
            //креираме простор за уште еден лет
            Flight *temp = new Flight[n+1];
            //копираме на постоечките летови во temp
            for (int i = 0; i < n; ++i) {
                temp[i] = letovi[i];
            }
            //го додаваме новиот лет во temp
            temp[n] = f;
            //ја бришеме динамички алоцираната низа/старта
            delete [] letovi;
            //
            letovi = temp;
            //го зголемуваме бројот на летови
            n++;
        }
    }
};

void searchFlights(Airline a, char departureCity[], char arrivalCity[]){

}

int main(){
    Flight f("SK", "OH", 1.5, 10);
    f.printDuration();
    return 0;
}