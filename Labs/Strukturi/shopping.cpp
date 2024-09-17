//
// Created by Teodora on 16.3.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

struct Item{
    char ime[30];
    int cena;
};

struct ShoppingCart{
    int id;
    int br_proizvodi;
    Item proizvod[100];

    void read() {
        cin >> id;
        cin >> br_proizvodi;
        for (int i = 0; i < br_proizvodi; ++i) {
            cin >> proizvod[i].ime;
            cin >> proizvod[i].cena;
        }
    }
};

void printAveragePriceOfLowestItems(ShoppingCart cart[], int n){
    int lowestPrices[n], lowestSum = 0;
    for (int i = 0; i < n; ++i) {
        int lowestInCart = cart[i].proizvod[0].cena;
        for (int j = 0; j < cart[i].br_proizvodi; ++j) {
            if(cart[i].proizvod[j].cena < lowestInCart){
                lowestInCart = cart[i].proizvod[j].cena;
            }
        }
        lowestPrices[i] = lowestInCart;
    }
    for (int i = 0; i < n; ++i) {
        lowestSum += lowestPrices[i];
    }

    cout<<"Average: "<<float(lowestSum) / n << endl;
}

void printHighestPricedItem(ShoppingCart cart[], int n){
    for (int i = 0; i < n; ++i) {
        int h = cart[i].proizvod[0].cena;
        char highestPricedItem[50];
        for (int j = 0; j < cart[i].br_proizvodi; ++j) {
            if (cart[i].proizvod[j].cena > h){
                h = cart[i].proizvod[j].cena;
                strcpy(highestPricedItem, cart[i].proizvod[j].ime);
            }
        }
        cout<<"Shopping cart id: "<<cart[i].id<<endl;
        cout<<"Product: "<<highestPricedItem<<endl;
    }
}

int main(){
    ShoppingCart s[10];
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        s[i].read();
    }
    printAveragePriceOfLowestItems(s, n);
    printHighestPricedItem(s, n);
    return 0;
}