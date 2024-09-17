//
// Created by Teodora on 03.6.2024.
//
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class EmbgLenghtIsNotValid{
private:
    string embg;
public:
    EmbgLenghtIsNotValid(string embg=""){
        this->embg = embg;
    }
    void message(){
        cout<<"EMBG "<<embg<<" must be 13 digit long!"<<endl;
    }
};

class EmbgFormatIsNotValid{
private:
    string embg;
public:
    EmbgFormatIsNotValid(string embg=""){
        this->embg = embg;
    }

    void message(){
        cout<<"EMBG "<<embg<<" must contain only digits!"<<endl;
    }
};

class Citizen{
private:
    string name;
    string embg;
public:
    Citizen(string name="", string embg=""){
        if(embg.length() != 13){
            throw EmbgLenghtIsNotValid(embg);
        }
        for (int i = 0; i < embg.length(); ++i) {
            if(!isdigit(embg[i])){
                throw EmbgFormatIsNotValid(embg);
            }
        }
        this->name = name;
        this->embg = embg;
    }
};

int main(){
    string name, embg;
    cin>>name>>embg;
    try{
        Citizen c(name, embg);
        cout<<"Citizen: "<<name<<" "<<embg<<" is created."<<endl;
    }catch (EmbgLenghtIsNotValid &e){
        e.message();
    }catch (EmbgFormatIsNotValid &f){
        f.message();
    }
    return 0;
}