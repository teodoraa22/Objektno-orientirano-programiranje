#include <bits/stdc++.h>
using namespace std;

//статичка
class LibraryFull{
public:
    void print(){
        cout<<"The library is already full"<<endl;
    }
};

//динамичка
class BookNotFound{
private:
    string bookTitle;
public:
    BookNotFound(string bookTitle=""){
        this->bookTitle=bookTitle;
    }
    void print(){
        cout<<"The book "<<bookTitle<<" does not exist"<<endl;
    }
};

class IndexOutOfRange{
public:
    void print(){
        cout<<"Index is out of range"<<endl;
    }
};

class Book{
private:
    string title;
    string author;
    int year;
public:

    Book(string title="", string author="", int year=0){
        this->year=year;
        this->author=author;
        this->title=title;
    }
    friend ostream &operator<<(ostream &out, Book &b){
        out<<b.title<<" "<<b.author<<" "<<b.year<<endl;
        return out;
    }

//    friend class Library;

    string getTitle(){
        return title;
    }

    string getAuthor(){
        return author;
    }
};

class Library{
private:
    string name;
    Book array[20];
//    Book *array;
    int n;
public:
    Library()=default;
    Library(string name=""){
        this->name=name;
    }
//    Library(string name="", Book *array=0, int n=0){
//        this->name=name;
//        this->n=n;
//        this->array=new Book[n];
//        for(int i=0;i<n;i++){
//            this->array[i]=array[i];
//        }
//    }
    Library &operator+=(Book b){
        if(n==20){
            throw LibraryFull();
        }
        array[n++]=b;
        return *this;
    }

    Library &operator-=(Book b){
        int flag=-1;

        for(int i=0; i<n; i++){
            if(array[i].getTitle()==b.getTitle()){
                flag=i;
                break;
            }
        }

        if(flag==-1){
            throw BookNotFound(b.getTitle());
        }
        else{
            for(int i=flag; i<(n-1); i++){
                array[i]=array[i+1];
            }
            n--;
        }

        return *this;
    }

    friend ostream &operator<<(ostream &out, Library &l){
        out<<l.name<<endl;
        for (int i = 0; i < l.n; ++i) {
            out<<l.array[i];
        }
        return out;
    }

    Book operator[](int index){
        if(index>=0 && index<n ){
            return array[index];
        }
        throw IndexOutOfRange();
    }

    Book *getBookbyAuthor(string author, int &numberFound){
        numberFound=0;
        Book books[20];
        for (int i = 0; i < n; ++i) {
            if(array[i].getAuthor()==author){
                books[numberFound++]=array[i] ;
            }
        }
        return books;
    }


};



int main(){
    ifstream dat("C:\\Users\\PC\\CLionProjects\\OOP_2023\\AV11\\biblioteka");
    if(!dat.is_open()){
        return -1;
    }
    string name;
    dat>>name;
    Library l(name);
    cout<<l;
    int n;
    dat>>n;
    dat.ignore();
    string title,author;
    int year;
    for (int i = 0; i <n ; ++i) {
        getline(dat, title);
        getline(dat, author);
        dat>>year;
        dat.ignore();
        Book b(title, author, year);
        try {
            l += b;
        }
        catch(LibraryFull l){
            l.print();
        }
    }
    cout<<l;
    Book b("title", "author", 2024);
    try{
        l-=b;
    }
    catch(BookNotFound k){
        k.print();
    }
    cout<<l;
    return 0;
}