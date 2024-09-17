#include <iostream>
#include <cstring>

using namespace std;

enum Tip {
    smartfon, kompjuter
};

class Device {
private:
    char model[100];
    Tip tip;
    static float casovi;
    int godina;
public:
    Device(const char* model = "", Tip tip = smartfon, int godina = 0) {
        strcpy(this->model, model);
        this->tip = tip;
        this->godina = godina;
    }

    static void setPocetniCasovi(float cas) {
        casovi = cas;
    }

    float proverka() const {
        float totalCasovi = casovi;
        if (godina > 2015) {
            totalCasovi += 1.5;
        }
        if (tip == kompjuter) {
            totalCasovi += 2;
        }
        return totalCasovi;
    }

    friend ostream& operator<<(ostream& o, const Device& d) {
        o << d.model << endl;
        o << (d.tip == smartfon ? "Mobilen" : "Laptop") << " " << d.proverka() << endl;
        return o;
    }

    int getGodina() const {
        return godina;
    }
};

class InvalidProductionDate {
public:
    void message() const {
        cout << "Невалидна година на производство" << endl;
    }
};

class MobileServis {
private:
    char adresa[100];
    Device* uredi;
    int n;
    void copy(const MobileServis& m) {
        strcpy(this->adresa, m.adresa);
        this->n = m.n;
        this->uredi = new Device[m.n];
        for (int i = 0; i < m.n; ++i) {
            this->uredi[i] = m.uredi[i];
        }
    }
public:
    MobileServis(const char* adresa = "") {
        strcpy(this->adresa, adresa);
        this->n = 0;
        this->uredi = new Device[0];
    }

    MobileServis(const MobileServis& m) {
        copy(m);
    }

    MobileServis& operator=(const MobileServis& m) {
        if (this != &m) {
            delete[] this->uredi;
            copy(m);
        }
        return *this;
    }

    MobileServis& operator+=(const Device& d) {
        if (d.getGodina() > 2019 || d.getGodina() < 2000) {
            throw InvalidProductionDate();
        }
        Device* temp = new Device[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = uredi[i];
        }
        temp[n++] = d;
        delete[] uredi;
        uredi = temp;
        return *this;
    }

    ~MobileServis() {
        delete[] uredi;
    }

    void pecatiCasovi() const {
        cout << "Ime: " << adresa << endl;
        for (int i = 0; i < n; ++i) {
            cout << uredi[i];
        }
    }
};

float Device::casovi = 1;

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (Tip)tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (Tip)tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate& d) {
                d.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (Tip)tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate& d) {
                d.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (Tip)tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate& d) {
                d.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (Tip)tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate& d) {
                d.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try {
                Device tmp(ime, (Tip)tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate& d) {
                d.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;
}