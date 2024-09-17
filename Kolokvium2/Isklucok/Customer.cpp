//
// Created by Teodora on 02.6.2024.
//
#include <iostream>
#include <cstring>
#include <stdexcept>
#define MAX 50

using namespace std;

enum typeC {
    standarden, lojalen, vip
};

class Customer {
private:
    char ime[MAX];
    char mail[MAX];
    typeC kupuvac;
    static int osnoven_popust;
    static int dopolnitelen_popust;
    int proizvodi;

public:
    Customer(const char *ime = "", const char *mail = "", typeC kupuvac = standarden, int proizvodi = 0) {
        strncpy(this->ime, ime, MAX);
        strncpy(this->mail, mail, MAX);
        this->kupuvac = kupuvac;
        this->proizvodi = proizvodi;
    }

    static void setDiscount1(int p) {
        osnoven_popust = p;
    }

    friend ostream &operator<<(ostream &o, const Customer &c) {
        o << c.ime << endl;
        o << c.mail << endl;
        o << c.proizvodi << endl;
        if (c.kupuvac == lojalen) {
            o << "loyal " << osnoven_popust << endl;
        } else if (c.kupuvac == vip) {
            o << "vip " << osnoven_popust + dopolnitelen_popust << endl;
        } else {
            o << "standard 0" << endl;
        }
        return o;
    }

    const char* getMail() const {
        return mail;
    }

    void setVid(typeC a) {
        kupuvac = a;
    }

    int getKupeni() const {
        return proizvodi;
    }

    typeC getVid() const {
        return kupuvac;
    }
};

int Customer::osnoven_popust = 10;
int Customer::dopolnitelen_popust = 20;

class UserExistsException {
public:
    void messages() {
        cout << "The user already exists in the list!" << endl;
    }
};

class FINKI_bookstore {
private:
    Customer *kupuvaci;
    int n;
public:
    FINKI_bookstore() : kupuvaci(nullptr), n(0) {}

    FINKI_bookstore(const FINKI_bookstore &other) {
        this->n = other.n;
        this->kupuvaci = new Customer[other.n];
        for (int i = 0; i < other.n; ++i) {
            this->kupuvaci[i] = other.kupuvaci[i];
        }
    }

    FINKI_bookstore& operator=(const FINKI_bookstore &other) {
        if (this != &other) {
            delete[] kupuvaci;
            this->n = other.n;
            this->kupuvaci = new Customer[other.n];
            for (int i = 0; i < other.n; ++i) {
                this->kupuvaci[i] = other.kupuvaci[i];
            }
        }
        return *this;
    }

    ~FINKI_bookstore() {
        delete[] kupuvaci;
    }

    void setCustomers(Customer *kupuvaci, int n) {
        delete[] this->kupuvaci;
        this->n = n;
        this->kupuvaci = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->kupuvaci[i] = kupuvaci[i];
        }
    }

    FINKI_bookstore& operator+=(const Customer &c) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(kupuvaci[i].getMail(), c.getMail()) == 0) {
                throw UserExistsException();
            }
        }
        Customer *temp = new Customer[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = kupuvaci[i];
        }
        temp[n++] = c;
        delete[] kupuvaci;
        kupuvaci = temp;
        return *this;
    }

    void update() {
        for (int i = 0; i < n; ++i) {
            if (kupuvaci[i].getVid() == standarden && kupuvaci[i].getKupeni() > 5) {
                kupuvaci[i].setVid(lojalen);
            } else if (kupuvaci[i].getVid() == lojalen && kupuvaci[i].getKupeni() > 10) {
                kupuvaci[i].setVid(vip);
            }
        }
    }

    friend ostream &operator<<(ostream &o, const FINKI_bookstore &f) {
        for (int i = 0; i < f.n; ++i) {
            o << f.kupuvaci[i];
        }
        return o;
    }
};

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int numProducts;

    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC)tC, numProducts);
        cout << c;
    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC)tC, numProducts);
        cout << c;

        Customer::setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;

        try {
            Customer c(name, email, (typeC)tC, numProducts);
            fc += c;
        } catch (UserExistsException &u) {
            u.messages();
        }

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);

        try {
            fc += c;
        } catch (UserExistsException &u) {
            u.messages();
        }
        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;
}