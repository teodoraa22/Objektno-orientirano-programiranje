//
// Created by Teodora on 17.5.2024.
//
/*
Да се имплементира класа Athlete за која се чува:
name (низа од карактери)
age (int)
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадениот атлетичар.

Потребно е да се имплементираат класите Runner и Jumper кои што ќе наследуваат од класата Athlete.

За класата Runner дополнително се чуваат:

speed - брзина на играчот(double)
Функцијата displayInfo() ја вклучува и брзината.

За класата Jumper дополнително се чуваат:

height- висина на скокачот (double)
Функцијата displayInfo() ја вклучува и висината.


Потребно е да се имплементира класата AllRoundAthlete која што ќе наследува од класите Runner и Jumper.

За класата AllRoundAthlete дополнително се чува:

stamina - стамина на AllRound играчот(int)

Функцијата displayInfo() печати вклучувајќи го и нивото на стамина.

Да се направи глобална функцијаAthlete* findAthleteWithMaxValue(Athlete** athletes, int n) - најголема вредност за тркачите се одредува според брзина, додека кај скокачите според висина, треба да се најде играчот кој ќе има најголема вредност и да се врати покажувач кон него.
 */
#include <iostream>
#include <cstring>

using namespace std;

class Athlete{
protected:
    char name[50];
    int age;
public:
    Athlete(char *name="", int age=0){
        strcpy(this->name, name);
        this->age = age;
    }

    virtual void displayInfo() = 0;
};

class Runner : virtual public Athlete{
protected:
    double speed;
public:
    Runner(char *name="", int age=0, double speed=0)
    : Athlete(name, age){
        this->speed = speed;
    }

    void displayInfo(){
        cout<<"Athlete: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Speed: "<<speed<<" mph"<<endl;
    }

    double getSpeed(){
        return speed;
    }
};

class Jumper : virtual public Athlete{
protected:
    double height;
public:
    Jumper(char *name="", int age=0, double height=0)
    : Athlete(name, age){
        this->height = height;
    }

    void displayInfo(){
        cout<<"Athlete: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Height: "<<height<<"m"<<endl;
    }

    double getHeight(){
        return height;
    }
};

class AllRoundAthlete : public Runner, public Jumper{
private:
    int stamina;
public:
    AllRoundAthlete(char *name="", int age=0, double speed=0, double height=0, int stamina=0){
        strcpy(this->name, name);
        this->age = age;
        this->height = height;
        this->speed = speed;
        this->stamina = stamina;
    }

    void displayInfo(){
        cout<<"Athlete: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Speed: "<<speed<<" mph"<<endl;
        cout<<"Height: "<<height<<"m"<<endl;
        cout<<"Stamina: "<<stamina<<endl;
    }
};

Athlete* findAthleteWithMaxValue(Athlete** athletes, int n) {
    int index = -1;
    double maxValue = -1;

    for(int i = 0; i < n; i++) {
        double newValue = 0;
        if(dynamic_cast<Runner*>(athletes[i]))
            newValue = dynamic_cast<Runner*>(athletes[i])->getSpeed();
        else if(dynamic_cast<Jumper*>(athletes[i]))
            newValue = dynamic_cast<Jumper*>(athletes[i])->getHeight();
        if(index == -1 || newValue > maxValue) {
            maxValue = newValue;
            index = i;
        }
    }

    if(index == -1) return nullptr;

    return athletes[index];
}

int main() {
    char name[50];
    int age;
    double speed;
    double height;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        cin>>age;
        AllRoundAthlete allRoundAthlete(name, age, 13.6, 1.80, 6);
        allRoundAthlete.displayInfo();
    }
    else {

        cin >> n;

        Athlete **athletes = new Athlete *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> age >> speed;

                athletes[i] = new Runner(name, age, speed);
            } else {
                cin >> name >> age >> height;

                athletes[i] = new Jumper(name, age, height);
            }

        }

        findAthleteWithMaxValue(athletes, n)->displayInfo();

    }


    return 0;
}
