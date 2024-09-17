//
// Created by Teodora on 13.3.2024.
//
#include<iostream>
#include<cmath>
using namespace std;

class Triagolnik{
private:
    int a;
    int b;
    int c;
public:
    Triagolnik(int aa, int bb, int cc){
        a = aa;
        b = bb;
        c = cc;
    }
    ~Triagolnik(){}
    int perimetar(){
        return a+b+c;
    }
    float plostina(){
        float s = perimetar()/2.0;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }
};

int main(){
    int a, b, c;
    cin>>a>>b>>c;
    Triagolnik t(a, b, c);
    cout<<t.perimetar()<<endl;
    cout<<t.plostina()<<endl;
    return 0;
}