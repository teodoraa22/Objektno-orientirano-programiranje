//
// Created by Teodora on 15.5.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class QuizAttempt{
protected:
    char indeks[7];
public:
    QuizAttempt(char *indeks){
        strcpy(this->indeks, indeks);
    }

    virtual double score() = 0;

    virtual void print() = 0;

    bool operator>=(QuizAttempt &q){
        return this->score()>=q.score();
    }
};

class MCQuizAttempt : public QuizAttempt{
private:
    char tocni[11];
    char odgovori[11];
public:
    MCQuizAttempt(char *indeks, char *tocni, char *odgovori)
    : QuizAttempt(indeks){
        strcpy(this->tocni, tocni);
        strcpy(this->odgovori, odgovori);
    }

    void print(){
        for (int i = 0; i < 10; ++i) {
            cout<<i+1<<". "<<"Correct: "<<tocni[i]<<" Answer: "<<odgovori[i];
            cout<<" Points: "<<(tocni[i] == odgovori[i] ? 1 : -0.25)<<endl;
        }
        cout<<"Total score: "<<score()<<endl;
    }

    double score(){
        double total = 0;
        for (int i = 0; i < 10; ++i) {
            if(tocni[i] == odgovori[i]){
                total += 1;
            }else{
                total -= 0.25;
            }
        }
        return total;
    }
};

class TFQuizAttempt : public QuizAttempt{
private:
    bool tocni[10];
    bool odgovori[10];
public:
    TFQuizAttempt(char *indeks, bool *tocni, bool *odgovori)
    : QuizAttempt(indeks){
        for (int i = 0; i < 10; ++i) {
            this->tocni[i] = tocni[i];
            this->odgovori[i] = odgovori[i];
        }
    }

    void print(){
        for (int i = 0; i < 10; ++i) {
            cout<<i+1<<". "<<"Correct: "<<(tocni[i] ? "True" : "False")<<" Answer: ";
            cout<<(odgovori[i] ? "Correct" : "False")<<" Points: "<<(tocni[i] == odgovori[i] ? 1 : -0.5)<<endl;
        }
        cout<<"Total score: "<<score()<<endl;
    }

    double score(){
        double total = 0;
        for (int i = 0; i < 10; ++i) {
            if(tocni[i] == odgovori[i]){
                total += 1;
            }else{
                total -= 0.5;
            }
        }
        return total;
    }
};

double averagePointsOfPassedStudents (QuizAttempt ** attempts, int n){
    double suma = 0;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if(attempts[i]->score() >= 5.0){
            suma += attempts[i]->score();
            count++;
        }
    }
    return suma / count;
}

QuizAttempt *readMCQuizAttempt() {
    char indeks[7];
    char tocni[11];
    char odgovori[10];

    cin>>indeks>>tocni>>odgovori;
    return  new MCQuizAttempt(indeks, tocni, odgovori);
}

QuizAttempt *readTFQuizAttempt() {
    char indeks[7];
    bool tocni[10];
    bool odgovori[10];

    cin>>indeks;
    for (int i = 0; i < 10; ++i) {
        cin>>tocni[i];
    }
    for (int i = 0; i < 10; ++i) {
        cin>>odgovori[i];
    }
    return new TFQuizAttempt(indeks, tocni, odgovori);
}

int main(){
    int testCase;

    cin >> testCase;

    if (testCase == 1) {
        cout << "Test MCQuizAttempt" << endl;
        QuizAttempt *attempt = readMCQuizAttempt();
        cout << "Score: " << attempt->score() << endl;
        attempt->print();
    } else if (testCase == 2) {
        cout << "Test TFQuizAttempt" << endl;
        QuizAttempt *attempt = readTFQuizAttempt();
        cout << "Score: " << attempt->score() << endl;
        attempt->print();
    } else if (testCase == 3) {
        cout << "Test operator >=" << endl;
        int n;
        cin >> n;
        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                attempts[i] = readMCQuizAttempt();
            } else {
                attempts[i] = readTFQuizAttempt();
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if ((*attempts[i]) >= (*attempts[j])) {
                        cout << i << " >= " << j << endl;
                    } else {
                        cout << i << " < " << j << endl;
                    }
                }
            }
        }
    } else {
        int n;
        cin >> n;
        QuizAttempt **attempts = new QuizAttempt *[n];
        for (int i = 0; i < n; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                attempts[i] = readMCQuizAttempt();
            } else {
                attempts[i] = readTFQuizAttempt();
            }
            attempts[i]->print();
            cout << endl;
        }

        cout << "Average score of passed students is: " << averagePointsOfPassedStudents(attempts, n) << endl;
    }
    return 0;
}