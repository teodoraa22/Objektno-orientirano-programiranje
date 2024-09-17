//
// Created by Teodora on 24.4.2024.
//
#include <iostream>
#include <cstring>
using namespace std;

enum Genre{
    HORROR, COMEDY, DOCUMENTARY
};

class Movie{
private:
    int ID;
    char ime[30];
    Genre zanr;
    double cena;
public:
    Movie(int ID, char ime[], Genre zanr, double cena){
        this->ID = ID;
        strcpy(this->ime, ime);
        this->zanr = zanr;
        this->cena = cena;
    }
    Movie(){}
    ~Movie(){}
    friend ostream &operator<<(ostream &output, Movie &m){
        output<<m.ime<<" "<<m.zanr<<" "<<m.cena<<endl;
        return output;
    }
    void print(){
        cout<<ime<<" "<<zanr<<" "<<cena<<endl;
    }
    bool operator==(Movie m){
        if(ID == m.ID){
            return true;
        }else{
            return false;
        }
    }
    double operator+=(double procent){
        cena += procent;
    }
    Genre getZanr(){
        return zanr;
    }
};

class Cinema{
private:
    char ime[40];
    Movie *movies;
    int n;
    static int LOYAL_DISCOUNT;
public:
    Cinema(char ime[]=""){
        strcpy(this->ime, ime);
        n = 0;
        movies = new Movie[n];
    }

    Cinema(const Cinema &c){
        strcpy(this->ime, c.ime);
        n = c.n;
        movies = new Movie[c.n];
        for (int i = 0; i < c.n; ++i) {
            movies[i] = c.movies[i];
        }
    }

    Cinema &operator=(Cinema &c){
        if(this!=&c){
            delete [] movies;
            strcpy(this->ime, c.ime);
            n = c.n;
            movies = new Movie[c.n];
            for (int i = 0; i < c.n; ++i) {
                movies[i] = c.movies[i];
            }
        }
        return *this;
    }

    ~Cinema(){
        delete [] movies;
    }

    Cinema operator+=(Movie m){
        Movie *pomosna = new Movie[n+1];
        for (int i = 0; i < n; ++i) {
            pomosna[i] = movies[i];
        }
        pomosna[n] = m;
        delete [] movies;
        movies = pomosna;
        n++;
        return *this;
    }

    bool operator<(Cinema c){
        if(n < c.n){
            return true;
        }else{
            return false;
        }
    }

    friend ostream &operator<<(ostream &output, Cinema &c){
        output<<c.ime<<" movies:"<<endl;
        for (int i = 0; i < c.n; ++i) {
            c.movies->print();
        }
        output<<LOYAL_DISCOUNT<<endl;
        return output;
    }

    static void setLOYAL_DISCOUNT(int i){
        LOYAL_DISCOUNT = i;
    }

    void increase(Genre genre, double percent){
        for(int i = 0; i < n; i++){
            if(movies[i].getZanr() == genre){
                movies[i] += percent;
            }
        }
    }

    int getN(){
        return n;
    }

    static Cinema smallestChoice(Cinema cinemas[], int numCinemas);
};

int Cinema::LOYAL_DISCOUNT = 0;

Cinema smallestChoice(Cinema cinemas[], int numCinemas){
    Cinema smallestCinema = cinemas[0];
    for(int i = 1; i < numCinemas; i++){
        if(cinemas[i].getN() < smallestCinema.getN()){
            smallestCinema = cinemas[i];
        }
    }
    return smallestCinema;
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 0: {
            cout << "TESTING MOVIE CONSTRUCTOR" << endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << "TEST PASSED" << endl;
            break;
        }
        case 1: {
            cout<<"TESTING MOVIE OPERATOR <<"<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 2: {
            cout<<"TESTING MOVIE OPERATOR +="<<endl;

            Movie movie1(0, "Imaginary", Genre::HORROR, 300);
            Movie movie2(1, "Hangover", Genre::COMEDY, 350);
            Movie movie3(2, "Stormy", Genre::DOCUMENTARY, 300);

            cout << movie1;
            cout << movie2;
            cout << movie3;

            movie1 += 15;
            movie2 += 25.5;
            movie3 += 37;

            cout << movie1;
            cout << movie2;
            cout << movie3;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 3: {
            cout<<"TESTING CINEMA CONSTRUCTOR and <<"<<endl;

            Cinema cinema("Cineplexx");
            cout << cinema;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 4: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(20);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 5: {
            cout<<"TESTING CINEMA OPERATOR += and <<"<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);

            Cinema cinema("Cineplexx");

            cinema += movie;
            cinema += movie1;
            cinema += movie2;
            cinema += movie2;

            Cinema::setLOYAL_DISCOUNT(25);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 6: {
            cout<<"TESTING CINEMA COPY-CONSTRUCTOR and OPERATOR ="<<endl;

            Movie movie(0, "Imaginary", Genre::HORROR, 300);
            Movie movie1(1, "Hangover", Genre::COMEDY, 350);
            Movie movie2(2, "Stormy", Genre::DOCUMENTARY, 300);
            Movie movie3(3, "Omen", Genre::HORROR, 300);
            Movie movie4(4, "Argylle", Genre::COMEDY, 350);

            Cinema cinema1("Cineplexx");

            cinema1 += movie;
            cinema1 += movie1;
            cinema1 += movie2;


            Cinema cinema2(cinema1);
            Cinema cinema4;
            {
                Cinema cinema3("Galaxy");
                cinema3 += movie3;
                cinema3 += movie4;
                cinema4 = cinema3;
            }

            cout << cinema2;
            cout << cinema4;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 7: {
            cout<<"TESTING CINEMA OPERATOR < "<<endl;
            Movie horror(0, "Imaginary", Genre::HORROR, 300);
            Movie comedy(1, "Hangover", Genre::COMEDY, 350);
            Movie documentary(2, "Stormy", Genre::DOCUMENTARY, 300);

            Movie horror1(0, "Omen", Genre::HORROR, 300);
            Movie comedy1(3, "Argylle", Genre::COMEDY, 350);
            Movie documentary1(2, "Christspiracy", Genre::DOCUMENTARY, 300);

            Cinema cinema1("Galaxy");
            cinema1 += horror;
            cinema1 += comedy;
            cinema1 += documentary;

            Cinema cinema2("Encore");
            cinema2 += horror1;
            cinema2 += comedy;
            cinema2 += comedy1;
            cinema2 += documentary1;

            if (cinema1 < cinema2) {
                cout << "TEST PASSED" << endl;
            }
            break;

        }
        case 8: {
            cout<<"TESTING METHOD increase"<<endl;

            char name[40];
            cin.ignore();
            cin.getline(name, 40);

            Cinema cinema(name);

            int n;
            cin >> n;

            int id;
            char title[30];
            int genre;
            float cost;
            float percent;

            for (int i = 0; i < n; i++) {
                cin >> id;
                cin.ignore();
                cin.getline(title, 30);
                cin >> genre;
                cin >> cost;

                Movie movie(id, title, (Genre) genre, cost);
                cinema += movie;
            }

            cin >> percent;
            cin >> genre;
            cout << cinema << endl;
            cinema.increase((Genre)genre, percent);
            cout << cinema << endl;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 9: {
            cout<<"TESTING METHOD smallestChoiceCinema"<<endl;

            int n;
            cin >> n;
            Cinema cinemas[n];
            char name[40];

            for (int i = 0; i < n; i++) {
                cin.ignore();
                cin.getline(name, 40);
                Cinema cinema(name);

                int m;
                cin >> m;

                int id;
                char title[30];
                int genre;
                float cost;

                for (int j = 0; j < m; j++) {
                    cin >> id;
                    cin.ignore();
                    cin.getline(title, 30);
                    cin >> genre;
                    cin >> cost;

                    Movie movie(id, title, (Genre) genre, cost);
                    cinema += movie;
                }

                cinemas[i] = cinema;
            }

            Cinema smallestChoiceCinema = smallestChoice(cinemas, n);
            cout << smallestChoiceCinema << endl;

            cout << "TEST PASSED" << endl;

            break;
        }
    }
    return 0;
}