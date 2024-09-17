//
// Created by Teodora on 11.4.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class Student{
private:
    char ime[20];
    int index;
    double prosek;
    static double vkupenProsek;
    static int vkupnoStudenti;
public:
    Student(char *ime="", double prosek=0.0){
        strcpy(this->ime, ime);
        this->prosek = prosek;
        index = 231001 + vkupnoStudenti;
        vkupnoStudenti++;
        vkupenProsek+=prosek;
    }
    ~Student(){}
    void pecati(){
        cout<<index<<" "<<ime<<" "<<prosek<<endl;
    }
    static double prosekNaSiteStudenti(){
        return vkupenProsek/vkupnoStudenti;
    };
};

int Student::vkupnoStudenti = 0;
double Student::vkupenProsek = 0;

int main (){
    Student stefan ("Stefan", 9.0);
    cout << Student::prosekNaSiteStudenti() << endl;

    Student petko ("Petko", 9.18);
    cout << Student::prosekNaSiteStudenti() << endl;

    Student riste ("Riste", 9.1);
    cout << Student::prosekNaSiteStudenti() << endl;

    Student trajce ("Trajce", 9.2);
    cout << Student::prosekNaSiteStudenti() << endl;

    Student ana ("Ana", 10.0);
    cout << Student::prosekNaSiteStudenti() << endl;

    stefan.pecati();
    petko.pecati();
    riste.pecati();
    trajce.pecati();
    ana.pecati();
    return 0;
}
