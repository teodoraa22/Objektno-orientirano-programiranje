//
// Created by Teodora on 01.6.2024.
//
#include <iostream>
#include <string>

using namespace std;

class InvalidSeatNumberException {
private:
    string message;
public:
    InvalidSeatNumberException(string message = "") {
        this->message = message;
    }
    void print()  {
        cout << message << endl;
    }
};

class Flight {
protected:
    string code;
    string departureCity;
    string arrivalCity;
    double price;
    double baggagePrice;
public:
    Flight(string code = "",  string departureCity = "",  string arrivalCity = "", double price = 0, double baggagePrice = 0){
        this->code = code;
        this->departureCity = departureCity;
        this->arrivalCity = arrivalCity;
        this->price = price;
        this->baggagePrice = baggagePrice;
    }

    double calculateTotalPrice()  {
        return price + baggagePrice;
    }

    void displayInfo()  {
        cout << code << " " << departureCity << "-" << arrivalCity << " " << price  << endl;
    }
};

class EconomyFlight : public Flight {
private:
    string seatNumber;
    static double LOYALTY_DISCOUNT;
public:
    EconomyFlight(Flight &f, string seatNumber = "")
            : Flight(f){
        this->seatNumber = seatNumber;
    }

    double calculateTotalPrice()  {
        double basePrice = Flight::calculateTotalPrice() * (1 - LOYALTY_DISCOUNT);
        if (seatNumber[0] == 'C' || seatNumber[0] == 'F') {
            basePrice *= 1.3;
        } else if (seatNumber[0] != 'A' && seatNumber[0] != 'B' && seatNumber[0] != 'C'&& seatNumber[0] != 'D' && seatNumber[0] != 'E' && seatNumber[0] != 'F') {
            throw InvalidSeatNumberException("Invalid Seat Number Exception");
        }
        return basePrice;
    }

    void displayInfo()  {
        cout  << code << " " << departureCity << "-" << arrivalCity << " " << seatNumber << endl;
        try{
            double totalPrice = calculateTotalPrice();
            cout << "Total Price: $" << totalPrice << endl;
        }
        catch (InvalidSeatNumberException e) {
            e.print();
        }
    }

    static void setLoyaltyDiscount(double discount) {
        LOYALTY_DISCOUNT = discount;
    }
};

double EconomyFlight::LOYALTY_DISCOUNT = 0.20;

int main() {
    int testCase;
    cin >> testCase;
    string code, from, to, seatNumber;
    double price, baggagePrice;

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ====" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
            Flight f(code, from, to, price, baggagePrice);
            EconomyFlight ec(f, seatNumber);
            ec.displayInfo();
        }
    } else if (testCase == 2) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
            Flight f(code, from, to, price, baggagePrice);
            try {
                EconomyFlight ec(f, seatNumber);
                ec.displayInfo();
            } catch (InvalidSeatNumberException e) {
                e.print();
            }
        }
    } else if (testCase == 3) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> code >> from >> to >> price >> baggagePrice >> seatNumber;
        Flight f(code, from, to, price, baggagePrice);
        EconomyFlight ec(f, seatNumber);
        ec.displayInfo();
        EconomyFlight::setLoyaltyDiscount(0.50);
        ec.displayInfo();
    }
    return 0;
}
