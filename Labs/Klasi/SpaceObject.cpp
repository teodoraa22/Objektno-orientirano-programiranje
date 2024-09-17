//
// Created by Teodora on 19.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class SpaceObject{
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    SpaceObject(char n[], char t[], int d){
        strcpy(name, n);
        strcpy(type, t);
        distanceFromEarth = d;
    }
    SpaceObject(){}
    ~SpaceObject(){}
    int get_distance(){
        return distanceFromEarth;
    }
    void print(){
        cout<<"["<<name<<"] (["<<type<<"]) - distance: ["<<distanceFromEarth<<"] light years away from Earth"<<endl;
    }
};

class Alien{
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;
    SpaceObject spaceObjects[50];
public:
    Alien(char name[], int age, char homePlanet[], int numObj, SpaceObject *spaceObjects){
        strcpy(this->name, name);
        this->age = age;
        strcpy(this->homePlanet, homePlanet);
        for (int i = 0; i < numObj; ++i) {
            this->spaceObjects[i] = spaceObjects[i];
        }
    }
    Alien(){}
    Alien(const Alien &a){
        strcpy(this->name, a.name);
        this->age = a.age;
        strcpy(this->homePlanet, a.homePlanet);
        for (int i = 0; i < numObj; ++i) {
            this->spaceObjects[i] = a.spaceObjects[i];
        }
    }
    ~Alien(){}
    void print(){
        cout<<"Alien name: "<<name<<endl;
        cout<<"Alien age: "<<age<<endl;
        cout<<"Alien homePlanet: "<<homePlanet<<endl;
        cout<<"Favourite space object closest to earth: "<<numObj<<endl;
        SpaceObject closest = getObjectClosestToEarth();
        closest.print();

    }
    SpaceObject getObjectClosestToEarth(){
        SpaceObject closest = spaceObjects[0];
        for (int i = 1; i < numObj; ++i) {
            if(spaceObjects[i].get_distance() < spaceObjects[0].get_distance()){
                closest = spaceObjects[i];
            }
        }
        return closest;
    }
};

int main(){
    char name[100], homePlanet[100];
    int age, numObj;
    cin>>name>>age>>homePlanet>>numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for(int i=0; i<numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin>>spaceObjectName>>spaceObjectType>>distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i]=SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien=Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}