//
// Created by Teodora on 26.4.2024.
//
#include <iostream>
#include <cstring>
using namespace std;

class NBAPlayer{
protected:
    char *ime;
    char tim[40];
    double poeni;
    double asistencii;
    double skokovi;
public:
    NBAPlayer(char *ime="", char tim[]="", double poeni=0, double asistencii=0, double skokovi=0){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->tim, tim);
        this->poeni = poeni;
        this->asistencii = asistencii;
        this->skokovi = skokovi;
    }

    NBAPlayer(const NBAPlayer &nba){
        this->ime = new char[strlen(nba.ime)+1];
        strcpy(this->tim, nba.tim);
        this->poeni = nba.poeni;
        this->asistencii = nba.asistencii;
        this->skokovi = nba.skokovi;
    }

    NBAPlayer &operator=(const NBAPlayer &nba){
        if(this!=&nba){
            delete [] ime;
            this->ime = new char[strlen(nba.ime)+1];
            strcpy(this->tim, nba.tim);
            this->poeni = nba.poeni;
            this->asistencii = nba.asistencii;
            this->skokovi = nba.skokovi;
        }
        return *this;
    }

    ~NBAPlayer(){
        delete [] ime;
    }

    double rating(){
        return poeni*0.45 + asistencii*0.3 + skokovi*0.25;
    }

    void print(){
        cout<<ime<<" - "<<tim<<endl;
        cout<<"Points: "<<poeni<<endl;
        cout<<"Assists: "<<asistencii<<endl;
        cout<<"Rebounds: "<<skokovi<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};

class AllStarPlayer : public NBAPlayer{
private:
    double natprevariPoeni;
    double natprevariAsistencii;
    double natprevariSkokovi;
public:
    AllStarPlayer(char *ime="", char tim[]="", double poeni=0, double asistencii=0, double skokovi=0,
                  double natprevariPoeni=0, double natprevariAsistencii=0, double natprevariSkokovi=0)
    : NBAPlayer(ime, tim, poeni, asistencii, skokovi){
        this->natprevariPoeni = natprevariPoeni;
        this->natprevariAsistencii = natprevariAsistencii;
        this->natprevariSkokovi = natprevariSkokovi;
    }

    AllStarPlayer(NBAPlayer nba, double natprevariPoeni=0, double natprevariAsistencii=0, double natprevariSkokovi=0)
    : NBAPlayer(nba){
        this->natprevariPoeni = natprevariPoeni;
        this->natprevariAsistencii = natprevariAsistencii;
        this->natprevariSkokovi = natprevariSkokovi;
    }

    AllStarPlayer(const AllStarPlayer &star): NBAPlayer(star){
        this->natprevariPoeni = star.natprevariPoeni;
        this->natprevariAsistencii = star.natprevariAsistencii;
        this->natprevariSkokovi = star.natprevariSkokovi;
    }

    AllStarPlayer &operator=(const AllStarPlayer &star){
        if(this!=&star){
            delete [] ime;
            NBAPlayer::operator=(star);
            this->natprevariPoeni = star.natprevariPoeni;
            this->natprevariAsistencii = star.natprevariAsistencii;
            this->natprevariSkokovi = star.natprevariSkokovi;
        }
        return *this;
    }

    ~AllStarPlayer(){}

    double allStarRating(){
        return natprevariPoeni*0.3 + natprevariAsistencii*0.4 + natprevariSkokovi*0.3;
    }

    double rating(){
        return (NBAPlayer::rating() + allStarRating()) / 2.0;
    }

    void print(){
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer *players = new NBAPlayer[5];
    AllStarPlayer *asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            players[i].print();
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name, team, points, assists, rebounds);
            asPlayers[i] = AllStarPlayer(players[i], allStarPoints, allStarAssists, allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints, allStarAssists, allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete[] players;
    delete[] asPlayers;

    return 0;
}