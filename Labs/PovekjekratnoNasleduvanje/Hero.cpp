//
// Created by Teodora on 17.5.2024.
//
/*
Да се имплементира апстрактна класа Hero за која се чува:
име - низа од знаци од максимум 40 знаци
attack damage - децимален број
attack speed - децимален број
ability power - децимален број
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за херојот и виртуелна функција float power() која ја враќа моќта на херојот.

Потребно е да се имплементира класите LegendaryHero и SuperHero кои што ќе наследуваат од класата Hero.

За класата LegendaryHero дополнително се чуваат:

hiddenPowers - број на скриени моќи (цел број)
Функцијата power() се пресметува со формулата (0.4*attack damage*hiddenPowers)+(0.25*attack speed*hiddenPowers)+(0.35*ability power*hiddenPowers)

Функцијата displayInfo() печати во формат:

LegendaryHero: [име]

Number of hidden powers: [hiddenPowers]

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]

За класата SuperHero дополнително се чуваат:

isShapeshifter - bool
Функцијата power() се пресметува со формулата attack damage+attack speed+ability power. Доколку е shapeshifter, тогаш неговата моќ се зголемува за два пати.

Функцијата displayInfo() печати во формат:

SuperHero: [име]

Shapeshifter: [Yes/No]

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]


Потребно е да се имплементира класата LegendarySuperHero која што ќе наследува од класите LegendaryHero и SuperHero.

Моќта е пресметана на следниот начин: (моќта на LegendaryHero + моќта на SuperHero)/2

Функцијата displayInfo() печати во формат:

LegendarySuperHero: [име]

Attack damage: [attack damage]

Attack speed: [attack speed]

Ability power: [ability power]

Power: [power]


Да се направи глобална функција Hero *mostPowerfulLegendaryHero(Hero **heroes, int n) што ќе врати покажувач до најмоќниот легендарен херој.
 * */
#include<iostream>
#include<cstring>
using namespace std;

class Hero{
protected:
    char ime[40];
    float attackDamage;
    float attackSpeed;
    float abilityPower;
public:
    Hero(char *ime="", float attackDamage=0, float attackSpeed=0, float abilityPower=0){
        strcpy(this->ime, ime);
        this->attackDamage = attackDamage;
        this->attackSpeed = attackSpeed;
        this->abilityPower = abilityPower;
    }

    virtual void displayInfo() = 0;
    virtual float power() = 0;
};

class LegendaryHero : virtual public Hero{
protected:
    int hiddenPowers;
public:
    LegendaryHero(char *ime="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, int hiddenPowers=0)
    : Hero(ime, attackDamage, attackSpeed, abilityPower){
        this->hiddenPowers = hiddenPowers;
    }

    float power(){
        return (0.4*attackDamage*hiddenPowers)+(0.25*attackSpeed*hiddenPowers)+(0.35*abilityPower*hiddenPowers);
    }

    void displayInfo(){
        cout<<"LegendaryHero: "<<ime<<endl;
        cout<<"Number of hidden powers: "<<hiddenPowers<<endl;
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

class SuperHero : virtual public Hero{
protected:
    bool isShapeshifter;
public:
    SuperHero(char *ime="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, bool isShapeshifter=false)
    : Hero(ime, attackDamage, attackSpeed, abilityPower){
        this->isShapeshifter = isShapeshifter;
    }

    float power(){
        if(isShapeshifter == true){
            return 2*(attackDamage+attackSpeed+abilityPower);
        }else{
            return attackDamage+attackSpeed+abilityPower;
        }
    }

    void displayInfo(){
        cout<<"SuperHero: "<<ime<<endl;
        if(isShapeshifter == true){
            cout<<"Shapeshifter: "<<"Yes"<<endl;
        }else{
            cout<<"Shapeshifter: "<<"No"<<endl;
        }
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

class LegendarySuperHero : public LegendaryHero, public SuperHero{
public:
    LegendarySuperHero(char *ime="", float attackDamage=0, float attackSpeed=0, float abilityPower=0, int hiddenPowers=0, bool isShapeshifter=false)
    : Hero(ime, attackDamage, attackSpeed, abilityPower){
        this->hiddenPowers = hiddenPowers;
        this->isShapeshifter = isShapeshifter;
    }
    float power(){
        return (LegendaryHero::power() + SuperHero::power()) / 2.0;
    }

    void displayInfo(){
        cout<<"LegendarySuperHero: "<<ime<<endl;
        cout<<"Attack damage: "<<attackDamage<<endl;
        cout<<"Attack speed: "<<attackSpeed<<endl;
        cout<<"Ability power: "<<abilityPower<<endl;
        cout<<"Power: "<<power()<<endl;
    }
};

Hero *mostPowerfulLegendaryHero(Hero **heroes, int n){
    Hero *mostPowerful = heroes[0];
    float maxPower = -1;
    for(int i = 0; i < n; ++i){
        if(dynamic_cast<LegendaryHero*>(heroes[i])){
            if(heroes[i]->power() > maxPower){
                maxPower = heroes[i]->power();
                mostPowerful = heroes[i];
            }
        }
    }
    return mostPowerful;
}

int main(){
    char name[50];
    double attackDamage;
    double attackSpeed;
    double abilityPower;
    int hiddenPowers;
    bool isShapeshifter;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>name;
        LegendarySuperHero legendarySuperHero(name, 55, 43, 70, 2, true);
        legendarySuperHero.displayInfo();
    }
    else {

        cin >> n;

        Hero **h = new Hero *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> name >> attackDamage >> attackSpeed >> abilityPower >> hiddenPowers;

                h[i] = new LegendaryHero(name, attackDamage, attackSpeed, abilityPower, hiddenPowers);
            } else {
                cin >> name >> attackDamage >> attackSpeed >> abilityPower >> isShapeshifter;

                h[i] = new SuperHero(name, attackDamage, attackSpeed, abilityPower, isShapeshifter);
            }

        }

        mostPowerfulLegendaryHero(h,n)->displayInfo();

    }
    return 0;
}