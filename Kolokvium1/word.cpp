//
// Created by Teodora on 03.4.2024.
//Да се дефинира класа Word во која ќе се чуваат информации за:
//Динамички алоцирана низа од знаци во која се чува содржината на зборот
//Број на појавување (честота) на зборот (цел број, иницијално 1)
//За класата да се имплементираат:
//Потребните конструктори, деструктор, set и get методи (10)
//Метод за печатење print() во формат Word: frequency (5)
//Метод increaseFrequency() за зголемување на честотата за 1 (3)
//Метод equals(const Word & w) за споредба дали содржината на зборот е иста со содржината на другиот збор.
//При споредбата да се игнорира големината на буквите. На пример, "word" == "WoRd" се евалуира во true. (7)

//Да се дефинира класа Text во која ќе се чуваат информации за:
//Динамички алоцирана низа од зборови (објекти од класата Word, иницијално празна)
//Големината на низата (цел број, иницијално 0).
//За класата Text да се имплементираат:
//Потребните конструктори, деструктор, set и get методи (10)
//Метод за печатење print() што ќе ги испечати сите зборови и нивните честоти, секој во посебен ред. (5)
//Метод за додавање на нов збор во текстот addWord(const Word & w). При додавање на нов збор во тексот прво да се провери
//дали веќе постои збор со иста содржина. Доколку постои таков збор, потребно е само да се зголеми честотата на зборот што веќе постои за 1.(15)
//Метод getFrequencyFor(char * word) што прима збор (низа од знаци), а како резултат ја враќа фреквенцијата на тој збор.
//Доколку зборот го нема во текстот, операторот треба да врати резултат -1. (10)

#include<iostream>
#include<cstring>
using namespace std;

class Word{
private:
    char *zbor;
    int frekvencija;
public:
    Word(char *zbor="", int frekvencija=1){
        this->zbor = new char[strlen(zbor) + 1];
        strcpy(this->zbor, zbor);
        this->frekvencija = frekvencija;
    }

    Word(const Word &w){
        this->zbor = new char[strlen(w.zbor) + 1];
        strcpy(this->zbor, w.zbor);
        this->frekvencija = w.frekvencija;
    }

    Word &operator=(Word &w){
        if(this != &w){   //proveruvame dali adresite se isti za da izbegneme samododeluvanje
            delete [] zbor;
            this->zbor = new char[strlen(w.zbor) + 1];
            strcpy(this->zbor, w.zbor);
            this->frekvencija = w.frekvencija;
        }
        return *this;
    }

    ~Word(){
        delete [] zbor;
    }

    void print(){
        cout<<zbor<<" "<<frekvencija<<endl;
    }

    Word &increaseFrequency(){
        frekvencija++;
        return *this;
    }

    bool equals(const Word & w){
        if(strlen(zbor) != strlen(w.zbor)){
            return false;
        }
        for (int i = 0; i < strlen(zbor); ++i) {
            if(tolower(zbor[i]) != tolower(w.zbor[i])){
                return false;
            }
        }
        return true;
    }

    int getFrekvencija(){
        return frekvencija;
    }
};

class Text{
private:
    Word *niza;
    int n; //golemina na niza
public:
    Text(){
        n=0;
        niza = new Word[n];
    }

    Text(const Text &t){
        n = t.n;
        niza = new Word[t.n];
        for (int i = 0; i < n; ++i) {
            niza[i] = t.niza[i];
        }
    }

    Text operator==(Text t){
        if(this != &t){
           delete [] niza;
            n = t.n;
            niza = new Word[t.n];
            for (int i = 0; i < n; ++i) {
                niza[i] = t.niza[i];
            }
        }
        return *this;
    }

    ~Text(){
        delete [] niza;
    }

    void addWord(const Word & w){
        for (int i = 0; i < n; ++i) {
            if(niza[i].equals(w)){
                niza[i].increaseFrequency();
                return;
            }
        }
        //zborot ne e pronajden ne postoi i treba da se dodade na krajot na nizata
        Word *temp = new Word[n+1]; //pravime temp niza od zborovi koja kje bide za 1 pogolema od n
        for (int i = 0; i < n; ++i) {
            temp[i] = niza[i]; // tuka se povikuva operatorot =
        }
        temp[n++] = w; // dodaj go elementot na posledna pozicija
        delete [] niza;  // izbrisi ja starata
        niza = temp;   // napravi ja starta da pokazuva kon novata niza
    }

    void print(){
        for (int i = 0; i < n; ++i) {
            niza[i].print();
        }
    }

    int getFrequencyFor(char *word){
        for (int i = 0; i < n; ++i) {
            if(niza[i].equals(word)){
                return niza[i].getFrekvencija();
            }
        }
        return -1;  //ne go nasol zborot
    }
};