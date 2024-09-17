//
// Created by Teodora on 02.6.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class SMS{
protected:
    float cena;
    char tel[20];
    static float TAX;
public:
    SMS(char *tel="", float cena=0){
        strcpy(this->tel, tel);
        this->cena = cena;
    }
    virtual float SMS_cena() const = 0;
    friend ostream &operator<<(ostream &o, SMS &s){
        o<<"Tel: "<<s.tel<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return o;
    }
};

float SMS::TAX = 18.0;

class RegularSMS : public SMS{
private:
    char poraka[1000];
    bool roaming;
    static float rProcent;
public:
    RegularSMS(char *tel="", float cena=0, char *poraka="", bool roaming=true)
    : SMS(tel, cena){
        strcpy(this->poraka, poraka);
        this->roaming = roaming;
    }

    float SMS_cena() const override{
        float price = cena * (strlen(poraka)/160 + 1) ;
        if (roaming){
            price += rProcent/100 * price;
        }else {
            price += TAX/100 * price;
        }
        return price;
    }

    static void set_rProcent(int p) {
        rProcent = p;
    }
};

float RegularSMS::rProcent = 300.0;

class SpecialSMS : public SMS{
private:
    bool humanitarni;
    static float sProcent;
public:
    SpecialSMS(char *tel="", float cena=0, bool humanitarni=true)
    : SMS(tel, cena){
        this->humanitarni = humanitarni;
    }

    float SMS_cena() const override{
        float price = cena;
        if (!humanitarni){
            return price += sProcent/100 * price;
        }else {
            return price;
        }
    }

    static void set_sProcent(int p) {
        sProcent = p;
    }
};

float SpecialSMS::sProcent = 150.0;

void vkupno_SMS(SMS** poraka, int n){
    int countSMS = 0;
    float vkupnoSMS = 0;
    int countSpecial = 0;
    float vkupno = 0;
    for (int i = 0; i < n; ++i) {
        if(dynamic_cast<SpecialSMS *>(poraka[i])){
            vkupno += poraka[i]->SMS_cena();
            countSpecial++;
        }else{
            vkupnoSMS += poraka[i]->SMS_cena();
            countSMS++;
        }
    }
    cout << "Vkupno ima " << countSMS << " regularni SMS poraki i nivnata cena e: " << vkupnoSMS << endl;
    cout << "Vkupno ima " << countSpecial << " specijalni SMS poraki i nivnata cena e: " << vkupno << endl;

}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}