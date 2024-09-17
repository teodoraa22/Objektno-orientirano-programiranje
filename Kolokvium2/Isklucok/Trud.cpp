//
// Created by Teodora on 02.6.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Trud{
private:
    char tip;
    int godina;
public:
    Trud(char tip='C', int godina=0){
        this->tip = tip;
        this->godina = godina;
    }

    friend istream &operator>>(istream &i, Trud &t){
        i>>t.tip>>t.godina;
        return i;
    }

    char getTip(){
        return tip;
    }

    int getGodina(){
        return godina;
    }
};

class Student{
protected:
    char ime[30];
    int indeks;
    int godina_upis;
    int *oceni;
    int br_oceni;
public:
    Student(char *ime="", int indeks=0, int godina_upis=0, int *oceni=0, int br_oceni=0){
        strcpy(this->ime, ime);
        this->indeks = indeks;
        this->godina_upis = godina_upis;
        this->br_oceni = br_oceni;
        this->oceni = new int[br_oceni];
        for (int i = 0; i < br_oceni; ++i) {
            this->oceni[i] = oceni[i];
        }
    }

    virtual double rang(){
        double vkupno = 0;
        for (int i = 0; i < br_oceni; ++i) {
            vkupno += oceni[i];
        }
        return (double)vkupno/br_oceni;
    }

    friend ostream &operator<<(ostream &o, Student &s){
        o<<s.indeks<<" "<<s.ime<<" "<<s.godina_upis<<" "<<s.rang()<<endl;
        return o;
    }

    int getIndeks(){
        return indeks;
    }
};

class Exception{
public:
    void message(){
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class PhDStudent : public Student{
private:
    Trud *trudovi;
    int br_trudovi;
    static int trudC;
    static int trudS;
public:
    PhDStudent(char *ime="", int indeks=0, int godina_upis=0, int *oceni=0, int br_oceni=0, Trud *trudovi=0, int br_trudovi=0)
    : Student(ime, indeks, godina_upis, oceni, br_oceni){
        int ctr = 0;
        for (int i = 0; i < br_trudovi; ++i) {
            if (trudovi[i].getGodina() < godina_upis) {
                Exception().message();
            }
            else ctr++;
        }
        this->br_trudovi = ctr;
        this->trudovi = new Trud[ctr];
        int j = 0;
        for (int i = 0; i < br_trudovi; ++i) {
            if (trudovi[i].getGodina() >= godina_upis) {
                this->trudovi[j++] = trudovi[i];
            }
        }

    }

    double rang() override{
        double rang = Student::rang();
        for (int i = 0; i < br_trudovi; ++i) {
            if(trudovi[i].getTip() == 'c' || trudovi[i].getTip() == 'C'){
                rang += trudC;
            }else{
                rang += trudS;
            }
        }
        return rang;
    }

    PhDStudent operator+=(Trud &t){
        if(t.getGodina() < godina_upis){
            throw Exception();
        }
        Trud *pomosna = new Trud[br_trudovi + 1];
        for (int i = 0; i < br_trudovi; ++i) {
            pomosna[i] = trudovi[i];
        }
        pomosna[br_trudovi++] = t;
        delete [] trudovi;
        trudovi = pomosna;
        return *this;
    }

    static void setTrudS(int journal){
        trudS = journal;
    }

    static void setTrudC(int conf){
        trudC = conf;
    }
};

int PhDStudent::trudC = 1;
int PhDStudent::trudS = 3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool p = false;
        for (int i = 0; i < m; ++i) {
            PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
            if (phd){
                try {
                    if (phd->getIndeks() == indeks) {
                        *phd += t;
                        p = true;
                    }
                }catch (Exception &e) {
                    e.message();
                }
            }
        }
        if (!p) cout << "Ne postoi PhD student so indeks " << indeks << '\n';

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        bool p = false;
        for (int i = 0; i < m; ++i) {
            PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
            if (phd){
                try {
                    if (phd->getIndeks() == indeks) {
                        *phd += t;
                        p = true;
                    }
                }catch (Exception &e) {
                    e.message();
                }
            }
        }
        if (!p) cout << "Ne postoi student so indeks " << indeks << '\n';

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        for (int i = 0; i < m; ++i) {
            PhDStudent* phd = dynamic_cast<PhDStudent *>(niza[i]);
            if (phd){
                try {
                    if (phd->getIndeks() == indeks) {
                        *phd += t;
                    }
                }catch (Exception &e) {
                    e.message();
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setTrudC(conf);
        PhDStudent::setTrudS(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}