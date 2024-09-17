//
// Created by Teodora on 02.6.2024.
//
#include <cstring>
#include <iostream>
using namespace std;

enum Size{
    mala, golema, familijarna // 0, 1, 2
};

// Your Code goes here
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    double cena;
public:
    Pizza(char *ime="", char *sostojki="", double cena=0){
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->cena = cena;
    }

    virtual double price() = 0;

    bool operator<(Pizza &other){
        return price() < other.price();
    }
};

class FlatPizza : public Pizza{
private:
    Size s;
public:
    FlatPizza(char *ime="", char *sostojki="", double cena=0, Size s=mala)
    : Pizza(ime, sostojki, cena){
        this->s = s;
    }

    double price() override{
        if(s == mala){
            return cena * 1.1;
        }else if(s == golema){
            return cena * 1.2;
        }else{
            return cena * 1.3;
        }
    }

    friend ostream &operator<<(ostream &o, FlatPizza &flat){
        o<<flat.ime<<": "<<flat.sostojki<<", ";
        if(flat.s == mala){
            o<<"small - "<<flat.price()<<endl;
        } else if(flat.s == golema){
            o<<"big - "<<flat.price()<<endl;
        } else{
            o<<"family - "<<flat.price()<<endl;
        }
        return o;
    }
};

class FoldedPizza : public Pizza{
private:
    bool beloBrasno;
public:
    FoldedPizza(char *ime="", char *sostojki="", double cena=0, bool beloBrasno=true)
    : Pizza(ime, sostojki, cena){
        this->beloBrasno = beloBrasno;
    }

    void setWhiteFlour(bool b) {
        beloBrasno = b;
    }

    double price() override{
        if(!beloBrasno){
            return cena * 1.3;
        }else{
            return cena * 1.1;
        }
    }

    friend ostream &operator<<(ostream &o, FoldedPizza &fold){
        o<<fold.ime<<": "<<fold.sostojki<<", ";
        if(!fold.beloBrasno){
            o<<"nwf - "<<fold.price()<<endl;
        }else{
            o<<"wf - "<<fold.price()<<endl;
        }
        return o;
    }
};

void expensivePizza(Pizza **pizza, int n) {
    int index = -1;
    Pizza *expensive = pizza[0];
    for (int i = 0; i < n; ++i) {
        if(pizza[i]->price() > expensive->price()){
            expensive = pizza[i];
            index = i;
        }
    }
    FlatPizza *flat = dynamic_cast<FlatPizza *>(pizza[index]);
    FoldedPizza *fold = dynamic_cast<FoldedPizza *>(pizza[index]);
    if(flat){
        cout<<*flat<<endl;
    }else if(fold){
        cout<<*fold<<endl;
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);
    }
    return 0;
}