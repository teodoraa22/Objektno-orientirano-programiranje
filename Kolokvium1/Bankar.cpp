//
// Created by Teodora on 10.4.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class StockRecord{
private:
    char ID[12];
    char ime[50];
    double kupeni;
    double cena;
    int n;        //broj na akcii
public:
    StockRecord(const char *ID="", const char *ime="", double kupeni=0.0, double cena=0.0, int n=0){
        strcpy(this->ID, ID);
        strcpy(this->ime, ime);
        this->kupeni = kupeni;
        this->cena = cena;
        this->n = n;
    }

    ~StockRecord(){}

    void setNewPrice(double c){
        cena = c;
    }

    double value(){
        return n * cena;
    }

    double profit() const{
        return n * (cena - kupeni);
    }

    friend ostream &operator<<(ostream &output,const StockRecord sr){
        output<<sr.ime<<" "<<sr.n<<" "<<sr.kupeni<<" "<<sr.cena<<" "<<sr.profit()<<endl;
        return output;
    }
};

class Client{
private:
    char imePrezime[60];
    int ID;
    StockRecord *kompanii;
    int n;              //broj na kompanii
public:
    Client(const char *imePrezime="", int ID=0){
        strcpy(this->imePrezime, imePrezime);
        this->ID = ID;
        n = 0;
        kompanii = new StockRecord[n];
    }

    Client(const Client &c){
        strcpy(this->imePrezime, c.imePrezime);
        this->ID = c.ID;
        n = c.n;
        kompanii = new StockRecord[c.n];
        for (int i = 0; i < n; ++i) {
            kompanii[i] = c.kompanii[i];
        }
    }

    Client &operator=(const Client &c){
        if(this != &c){
            delete [] kompanii;
            strcpy(this->imePrezime, c.imePrezime);
            this->ID = c.ID;
            n = c.n;
            kompanii = new StockRecord[c.n];
            for (int i = 0; i < n; ++i) {
                kompanii[i] = c.kompanii[i];
            }
        }
        return *this;
    }

    ~Client(){}

    double totalValue() const{
        double zbir = 0;
        for (int i = 0; i < n; ++i) {
            zbir += kompanii[i].value();
        }
        return zbir;
    }

    Client &operator+=(const StockRecord &c){
        StockRecord *temp = new StockRecord[n+1];
        for (int i = 0; i < n; ++i) {
            temp[i] = kompanii[i];
        }
        temp[n] = c;
        delete [] kompanii;
        kompanii = temp;
        n++;
        return *this;
    }

    friend ostream &operator<<(ostream &cout, const Client c){
        cout<<c.ID<<" "<<c.totalValue()<<endl;
        for (int i = 0; i < c.n; ++i) {
            cout<<c.kompanii[i];
        }
        return cout;
    }
};

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}