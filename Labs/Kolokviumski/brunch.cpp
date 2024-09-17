//
// Created by Teodora on 24.4.2024.
//
#include <iostream>
#include <cstring>

using namespace std;

enum Type{
    APPETIZER, MAINCOURSE, DESSERT
};

class Brunch{
private:
    int ID;
    char ime[30];
    double cena;
    Type tip;
public:
    Brunch(char ime[]="", int ID=0, double cena=0, Type tip=APPETIZER){
        strcpy(this->ime, ime);
        this->ID = ID;
        this->cena = cena;
        this->tip = tip;
    }

    ~Brunch(){}

    friend ostream &operator<<(ostream &out, Brunch &b){
        out<<b.ime<<" "<<b.cena<<" "<<b.tip<<endl;
        return out;
    }

    void print(){
        cout<<ime<<" "<<cena<<" "<<tip<<endl;
    }

    bool operator==(Brunch b){
        if(ID == b.ID){
            return true;
        }else{
            return false;
        }
    }

    double operator-=(double procent){
        cena -= procent;
    }

    Type getType(){
        return tip;
    }
};

class Restaurant{
private:
    char ime[40];
    Brunch *brunches;
    int n;
    static int LOYAL_DISCOUNT;
public:
    Restaurant(char ime[]=""){
        strcpy(this->ime, ime);
        n=0;
        brunches = new Brunch[n];
    }

    Restaurant(const Restaurant &r){
        strcpy(this->ime, r.ime);
        n=r.n;
        brunches = new Brunch[r.n];
        for (int i = 0; i < r.n; ++i) {
            brunches[i] = r.brunches[i];
        }
    }

    Restaurant &operator=(Restaurant &r){
        if(this!=&r){
           delete [] brunches;
            strcpy(this->ime, r.ime);
            n=r.n;
            brunches = new Brunch[r.n];
            for (int i = 0; i < r.n; ++i) {
                brunches[i] = r.brunches[i];
            }
        }
        return *this;
    }

    ~Restaurant(){
        delete [] brunches;
    }

    Restaurant operator+=(Brunch m){
        Brunch *pomosna = new Brunch[n+1];
        for (int i = 0; i < n; ++i) {
            pomosna[i] = brunches[i];
        }
        pomosna[n] = m;
        delete [] brunches;
        brunches = pomosna;
        n++;
        return *this;
    }

    bool operator>(Restaurant r){
        if(n > r.n){
            return true;
        }else{
            return false;
        }
    }

    friend ostream &operator<<(ostream &out, Restaurant &r){
        out<<r.ime<<" brunches:"<<endl;
        for (int i = 0; i < r.n; ++i) {
            r.brunches[i].print();
        }
        out<<LOYAL_DISCOUNT<<endl;
        return out;
    }

    static void setLOYAL_DISCOUNT(int i){
        LOYAL_DISCOUNT = i;
    }

    static Restaurant biggestMenu(Restaurant restaurants[], int numRestaurants);

    int getN(){
        return n;
    }

    void decrease(Type type, float d){
        for (int i = 0; i < n; ++i) {
            if(brunches[i].getType() == type){
                brunches[i] -= d;
            }
        }
    }
};

int Restaurant::LOYAL_DISCOUNT = 0;

Restaurant biggestMenu(Restaurant restaurant[], int numRestaurants){
    Restaurant biggestMenu = restaurant[0];
    for(int i = 1; i < numRestaurants; i++){
        if(restaurant[i].getN() > biggestMenu.getN()){
            biggestMenu = restaurant[i];
        }
    }
    return biggestMenu;
}

int main() {
    int test_case;
    cin >> test_case;
    switch (test_case) {
        case 0: {
            cout << "TESTING BRUNCH CONSTRUCTOR" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << "TEST PASSED" << endl;
            break;
        }
        case 1: {
            cout << "TESTING BRUNCH OPERATOR <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 2: {
            cout << "TESTING BRUNCH OPERATOR -=" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            appetizer -= 10;
            mainCourse -= 20.2;
            mainCourse -= 25;

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 3: {
            cout << "TESTING RESTAURANT CONSTRUCTOR and <<" << endl;

            Restaurant restaurant("Little Italy");
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 4: {
            cout << "TESTING RESTAURANT OPERATOR += and <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;

            Restaurant::setLOYAL_DISCOUNT(15.5);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 5: {
            cout << "TESTING RESTAURANT OPERATOR += and <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;
            restaurant += dessert;

            Restaurant::setLOYAL_DISCOUNT(20);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;

        }
        case 6: {
            cout << "TESTING RESTAURANT COPY-CONSTRUCTOR and OPERATOR =" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);
            Brunch appetizer1("Caprese", 4, 150, Type::APPETIZER);
            Brunch dessert1("Mousse", 5, 350, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;

            Restaurant restaurant2(restaurant);
            Restaurant restaurant4;
            {
                Restaurant restaurant3("Galaxy");
                restaurant3 += appetizer1;
                restaurant3 += dessert1;
                restaurant4 = restaurant3;
            }

            cout << restaurant2;
            cout << restaurant4;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 7: {
            cout << "TESTING RESTAURANT OPERATOR > " << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch appetizer1("Caprese", 1, 150, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch mainCourse1("Seafood", 2, 500, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);
            Brunch dessert1("Mousse", 4, 300, Type::DESSERT);


            Restaurant restaurant1("Little Italy");
            restaurant1 += appetizer;
            restaurant1 += mainCourse;
            restaurant1 += dessert;


            Restaurant restaurant2("Ember");
            restaurant2 += appetizer1;
            restaurant2 += mainCourse1;
            restaurant2 += dessert;
            restaurant2 += dessert1;


            if (restaurant2 > restaurant1) {
                cout << "TEST PASSED" << endl;
            }

            break;
        }
        case 8: {
            cout << "TESTING METHOD decrease" << endl;

            char rName[40];
            cin.ignore();
            cin.getline(rName, 40);
            Restaurant restaurant(rName);

            int n;
            cin >> n;

            char name[30];
            int id;
            float cost;
            int type;

            for (int i=0; i<n; i++) {
                cin.ignore();
                cin.getline(name,30);
                cin >> id;
                cin >> cost;
                cin >> type;

                Brunch brunch(name, id, cost, (Type)type);
                restaurant+=brunch;
                restaurant+=brunch;
            }

            float perc;
            cin >> perc;
            cin >> type;

            cout << restaurant;
            restaurant.decrease((Type)type, perc);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 9: {
            cout << "TESTING METHOD biggestMenuRestaurant" << endl;

            int n;
            cin >> n;
            Restaurant restaurants[n];

            char rName[40];

            for (int i=0; i<n; i++) {
                cin.ignore();
                cin.getline(rName, 40);
                Restaurant restaurant(rName);

                int m;
                cin >> m;

                char name[30];
                int id;
                float cost;
                int type;

                for (int j=0; j<m; j++) {
                    cin.ignore();
                    cin.getline(name,30);
                    cin >> id;
                    cin >> cost;
                    cin >> type;

                    Brunch brunch(name, id, cost, (Type)type);
                    restaurant+=brunch;
                }

                restaurants[i]=restaurant;

            }

            Restaurant biggestMenuRestaurant = biggestMenu(restaurants, 2);
            cout << biggestMenuRestaurant;

            cout << "TEST PASSED" << endl;

            break;
        }
    }

    return 0;
}