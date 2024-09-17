//
// Created by Teodora on 05.3.2024.
//
#include<iostream>

using namespace std;

struct Date{
    int day;
    int mouth;
    int year;

    void read(){
        cin>>day>>mouth>>year;
    }

    void print(){
        cout<<day<<"."<<mouth<<"."<<year<<endl;
    }
};

int compare(Date d1, Date d2) {
    if(d1.year > d2.year){
        return 1;
    }
    else if(d2.year > d1.year){
        return -1;
    }
    else{
        if(d1.mouth > d2.mouth){
            return 1;
        }
        else if(d2.mouth > d1.mouth){
            return -1;
        }
        else{
            if(d1.day > d2.day){
                return 1;
            }
            else if(d2.day > d1.day){
                return -1;
            }
            else{
                return 0;
            }
        }
    }
}

int daysDiff(Date d1, Date d2){
    return (d1.year - d2.year) * 360 + (d1.mouth - d2.mouth) * 30 + (d1.day - d2.day);
}

int main(){
    Date d1;
    Date d2;

    d1.read();
    d2.read();

    d1.print();
    d2.print();

    int rez = compare(d1, d2);
    if(rez == 0){
        cout<<"Datumite se ednakvi";
    }
    else if(rez > 0){
        cout<<"Razlikata vo denovi e "<<daysDiff(d1, d2)<<endl;
    }
    else{
        cout<<"Razlikata vo denovi e "<<daysDiff(d2, d1)<<endl;
    }
    return 0;
}