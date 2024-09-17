//
// Created by Teodora on 04.4.2024.
//
#include<iostream>
#include<cstring>
using namespace std;

class List{
private:
    int *broevi;
    int n;  // brojot na broevi
public:
    List(int *broevi=0, int n=0){
        n = 0;
        broevi = new int[n];
    }

    List(const List &l){
        n = l.n;
        for (int i = 0; i < n; ++i) {
            broevi[i] = l.broevi[i];
        }
    }

    List &operator=(List &l){
        delete [] broevi;
        n = l.n;
        for (int i = 0; i < n; ++i) {
            broevi[i] = l.broevi[i];
        }
        return *this;
    }

    ~List(){}

    int sum() {
        int sum=0;
        for (int i = 0; i < n; ++i) {
            sum += broevi[i];
        }
        return sum;
    }

    double average(){
        return double(sum()) / n;
    }

    void pecati(){
        cout<<n<<": ";
        for (int i = 0; i < n; ++i) {
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }

    int getN() {
        return n;
    }
};

class ListContainer{
private:
    List *listovi;
    int n;      //broj na listovi
    int obidi;
public:
    ListContainer(){
        n = 0;
        listovi = new List[n];
        obidi = 0;
    }

    ListContainer(const ListContainer &lc){
        n = lc.n;
        listovi = new List[lc.n];
        for (int i = 0; i < n; ++i) {
            listovi[i] = lc.listovi[i];
        }
    }

    ListContainer &operator=(const ListContainer &lc){
        if(this != &lc){
            delete [] listovi;
            n = lc.n;
            listovi = new List[lc.n];
            for (int i = 0; i < n; ++i) {
                listovi[i] = lc.listovi[i];
            }
        }
        return *this;
    }

    ~ListContainer(){
        delete [] listovi;
    }

    int sum(){
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += listovi[i].sum();
        }
        return sum;
    }

    double average(){
        int N=0;
        for (int i = 0; i < n; ++i) {
            N += listovi[i].getN();
        }
        return double(sum() / N);
    }

    void print(){
        if(n==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for (int i = 0; i < n; ++i) {
            cout<<"List number: "<<i+1<<" List info: ";
            listovi[i].pecati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<n<<" Failed attempts: "<<n-obidi<<endl;
    }

    void addNewList(List l) {
        for (int i = 0; i < n; ++i) {
            if(listovi[i].sum() == l.sum()){
                obidi++;
                return;
            }
        }
        List *temp = new List[n+1];
        for (int i = 0; i < n; ++i) {
            temp[i] = listovi[i];
        }
        temp[n] = l;
        delete [] listovi;
        listovi = temp;
        n++;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}