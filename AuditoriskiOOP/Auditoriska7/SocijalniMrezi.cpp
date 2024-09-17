//
// Created by Teodora on 14.5.2024
//
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

class User{
private:
    char *username;
    char *companyname;
    int pozicija;
public:
    //konstruktor so podrazbirlivi argumenti
    User(char *username="", char *companyname="", int pozicija=0){
        this->username = new char[strlen(username)+1];
        strcpy(this->username, username);
        this->companyname = new char[strlen(companyname)+1];
        strcpy(this->companyname, companyname);
        this->pozicija = pozicija;
    }

    //copy konstruktor
    User(const User &u){
        this->username = new char[strlen(u.username)+1];
        strcpy(this->username, u.username);
        this->companyname = new char[strlen(u.companyname)+1];
        strcpy(this->companyname, u.companyname);
        this->pozicija = u.pozicija;
    }

    //operator =
    User &operator=(const User &u){
        if(this!=&u){
            delete [] username;
            delete [] companyname;
            this->username = new char[strlen(u.username)+1];
            strcpy(this->username, u.username);
            this->companyname = new char[strlen(u.companyname)+1];
            strcpy(this->companyname, u.companyname);
            this->pozicija = u.pozicija;
        }
        return *this;
    }

    //destruktor
    ~User(){
        delete [] username;
        delete [] companyname;
    }

    //operator za vcituvanje podatoci
    friend istream &operator>>(istream &input, User &u){
        input>>u.username>>u.companyname>>u.pozicija;
        return input;
    }

    //operator za pecatenje podatoci
    friend ostream &operator<<(ostream &output, User &u){
        output<<"Username: "<<u.username<<", Company Name: "<<u.companyname<<", Pozicija: "<<u.pozicija<<endl;
        return output;
    }

    //operator za sporedba dali vekje postoi korisnik so takov username
    bool operator==(User &u){
        return strcmp(this->username, u.username) == 0;
    }

    int getPozicija() const{
        return pozicija;
    }

    char *getUsername(){
        return username;
    }
};

class Group{
protected:
    User *korisnici;
    int n; //broj na korisnici
    string ime;
public:
    //konstruktor so podrazbirlivi argumenti
    Group(string ime=""){
        this->ime = ime;
        n = 0;
        korisnici = new User[n];
    }

    //copy konstruktor
    Group(const Group &g){
        this->ime = g.ime;
        this->n = g.n;
        korisnici = new User[g.n];
        for (int i = 0; i < n; ++i) {
            korisnici[i] = g.korisnici[i];
        }
    }

    //operator =
    Group &operator=(const Group &g){
        if(this!=&g){
            delete [] korisnici;
            this->ime = g.ime;
            this->n = g.n;
            korisnici = new User[g.n];
            for (int i = 0; i < n; ++i) {
                korisnici[i] = g.korisnici[i];
            }
        }
        return *this;
    }

    //destruktor
    ~Group(){
        delete [] korisnici;
    }

    //metod za dodavanje nov clen
    virtual void addMember (User & u){
        //proveruvame dali postoi korisnik so ist username
        for (int i = 0; i < n; ++i) {
            if(strcmp(korisnici[i].getUsername(), u.getUsername()) == 0){
                return;
            }
        }
        //ako nema go dodavame
        User *pomosna = new User[n+1];
        for (int i = 0; i < n; ++i) {
            pomosna[i] = korisnici[i];
        }
        pomosna[n++] = u;
        delete [] korisnici;
        korisnici = pomosna;
    }

    //prosecno nivo na pozicii na clenovite
    double averagePosition() const{
        if(n == 0){
            return 0;
        }
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += korisnici[i].getPozicija();
        }
        return double(sum) / n;
    }

    //metod koj go presmetuva rejtingot na grupata
    virtual double rating() const{
        return (10 - averagePosition()) * n / 100;
    }

    //operator za pecatenje
    friend ostream &operator<<(ostream &output, Group &g){
        output<<"Ime na grupata: "<<g.ime<<", Broj na clenovi: "<<g.n<<", Rejting: "<<g.rating()<<endl;
        output<<"Lista na korisnici: "<<endl;
        for (int i = 0; i < g.n; ++i) {
            output<<g.korisnici[i]<<endl;
        }
        return output;
    }
};

class PrivateGroup : public Group{
private:
    static int KAPACITET;
    static const double KOEFICIENT;
public:
    PrivateGroup(string ime="") : Group(ime) {};

    PrivateGroup(const PrivateGroup &pg) : Group(pg) {};

    PrivateGroup &operator=(const PrivateGroup &pg){
        if(this!=&pg){
            Group::operator=(pg);
        }
        return *this;
    }

    void addMember (User & u){
        if(this->n == KAPACITET){
            return;
        }
        Group::addMember(u);
    }

    double rating() const{
        return (10 - averagePosition()) * (n / KAPACITET) * KOEFICIENT;
    }

    friend ostream &operator<<(ostream &output, PrivateGroup &pg){
        output<<"Privatna grupa: ";
        Group group(pg);
        output<<group;
        return output;
    }

    static void setCapacity(int kapacitet){
        KAPACITET = kapacitet;
    }
};

int PrivateGroup::KAPACITET = 10;
const double PrivateGroup::KOEFICIENT = 0.8;

int main(){
    cout << "INTEGRATION TEST" << endl;
    char name[50];
    int nGroups;
    cin >> nGroups;
    Group **groups = new Group *[nGroups];
    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type;
        cin >> name;
        if (type == 1) { //normal group
            groups[i] = new Group(name);
        } else { //private group
            groups[i] = new PrivateGroup(name);
        }
        int nUsers;
        cin >> nUsers;
        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;

            groups[i]->addMember(u);

        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
    PrivateGroup::setCapacity(15);
    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; ++i) {
        cout << *groups[i];
    }
    return 0;
}