//
// Created by Teodora on 30.5.2024.
//
#include<iostream>
#include<string>
using namespace std;

class Server{
protected:
    string IP;
    string host;
public:
    Server(string IP="", string host=""){
        this->IP = IP;
        this->host = host;
    }

    virtual double total_price() = 0;
};

class DedicatedServer : public Server{
private:
    double osnovna_cena;
    int RAM;
    int *hardDisks;
    int n; //broj na hard diskovi
public:
    DedicatedServer(string IP="", string host="", double osnovna_cena=0, int RAM=0)
    : Server(IP, host){
        this->osnovna_cena = osnovna_cena;
        this->RAM = RAM;
        n = 0;
        hardDisks = new int[n];
    }

    int hardDisk_prostor(){
        int vkupno = 0;
        for (int i = 0; i < n; ++i) {
            vkupno += hardDisks[i];
        }
        return vkupno;
    }

    double total_price(){
        return osnovna_cena + hardDisk_prostor() * 0.5 + RAM * 20;
    }

    DedicatedServer &operator+=(int size){
        int *pomosna = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            pomosna[i] = hardDisks[i];
        }
        pomosna[n++] = size;
        delete [] hardDisks;
        hardDisks = pomosna;
        return *this;
    }

    DedicatedServer &operator++(int){
        DedicatedServer kopija = *this;
        RAM++;
        return kopija;
    }

    friend ostream &operator<<(ostream &o, DedicatedServer &d){
        o<<d.host<<": "<<d.IP<<endl;
        o<<d.osnovna_cena<<", "<<d.RAM<<endl;
        o<<d.n<<", "<<d.hardDisk_prostor()<<endl;
        return o;
    }

    friend bool operator>(Server &s1, Server &s2);
};

class VirtualServer : public Server{
private:
    int jadra;
    int mesecen_protok;
public:
    VirtualServer(string IP="", string host="", int jadra=0, int mesecen_protok=0)
    : Server(IP, host){
        this->jadra = jadra;
        this->mesecen_protok = mesecen_protok;
    }

    double total_price(){
        return jadra * 5 + mesecen_protok * 10;
    }

    VirtualServer &operator+=(int vrednost){
        jadra += vrednost;
    }

    VirtualServer &operator++(int){
        VirtualServer kopija = *this;
        mesecen_protok++;
        return kopija;
    }

    friend ostream &operator<<(ostream &o, VirtualServer &v){
        o<<v.host<<": "<<v.IP<<endl;
        o<<v.jadra<<", "<<v.mesecen_protok<<endl;
        return o;
    }

    friend bool operator>(Server &s1, Server &s2);
};

bool operator>(Server &s1, Server &s2){
    return s1.total_price() > s2.total_price();
}

double totalCost(Server **serveri, int n){
    double totalCost = 0;
    for (int i = 0; i < n; ++i) {
        totalCost += serveri[i]->total_price();
    }
    return totalCost;
}

Server &biggestInvoice(Server **serveri, int n){
    Server *biggest = serveri[0];
    for (int i = 0; i < n; ++i) {
        if(serveri[i]->total_price() > biggest->total_price()){
            biggest = serveri[i];
        }
    }
    return *biggest;
}

int main() {
    int test_case;
    char hostname[101];
    char ip[46];
    int ram;
    int basic_price;
    int disk_space;
    int num_cores;
    int bandwith;

    int num_inc;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case Business Invoice - Constructor, operator <<
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer ds(ip, hostname, basic_price, ram);
        cout << ds;
    } else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer ds(ip, hostname, basic_price, ram);
        cout << ds;

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            ds++;
        }
        cout << ds;
    } else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<,
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer ds(ip, hostname, basic_price, ram);
        cout << ds;

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            ds++;
        }

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            cin >> disk_space;
            ds += disk_space;
        }

        cout << ds;
    } else if (test_case == 4) {
        cin >> ip >> hostname;
        cin >> basic_price >> ram;
        DedicatedServer ds(ip, hostname, basic_price, ram);
        cout << ds;
        cout << ds.total_price();
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            ds++;
        }

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            cin >> disk_space;
            ds += disk_space;
        }

        cout << ds;
        cout << ds.total_price();

    } else if (test_case == 5) {
        cin >> ip >> hostname;
        cin >> num_cores >> bandwith;
        VirtualServer vs(ip, hostname, num_cores, bandwith);
        cout << vs;
    } else if (test_case == 6) {
        cin >> ip >> hostname;
        cin >> num_cores >> bandwith;
        VirtualServer vs(ip, hostname, num_cores, bandwith);
        cout << vs;
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            vs++;
        }

        cin >> num_inc;
        vs += num_inc;

        cout << vs;

    } else if (test_case == 7) {
        cin >> ip >> hostname;
        cin >> num_cores >> bandwith;
        VirtualServer vs(ip, hostname, num_cores, bandwith);
        cout << vs;
        cout << vs.total_price() << endl;

        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            vs++;
        }

        cin >> num_inc;
        vs += num_inc;
        cout << vs;
        cout << vs.total_price();
    } else if (test_case == 8) {

        int num_servers;
        int server_type;

        cin >> num_servers;
        Server **s = new Server *[num_servers];
        for (int j = 0; j < num_servers; ++j) {

            cin >> server_type;
            if (server_type == 1) {
                cin >> ip >> hostname;
                cin >> basic_price >> ram;
                DedicatedServer *dsp =
                        new DedicatedServer(ip, hostname, basic_price, ram);

                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*dsp)++;
                }

                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> disk_space;
                    (*dsp) += disk_space;
                }

                cout << *(dsp);
                cout << dsp->total_price() << endl;

                s[j] = dsp;
            }
            if (server_type == 2) {

                cin >> ip >> hostname;
                cin >> num_cores >> bandwith;
                VirtualServer *vsp =
                        new VirtualServer(ip, hostname, num_cores, bandwith);

                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*vsp)++;
                }

                cin >> num_inc;
                (*vsp) += num_inc;

                cout << (*vsp);
                cout << vsp->total_price() << endl;
                s[j] = vsp;
            }
        }

        cout << "The cost of all servers is:\n";
        cout << totalCost(s, num_servers);
        cout << endl;

        cout << "Biggest invoice:\n";
        Server &server = biggestInvoice(s, num_servers);

        Server *ss = &server;
        DedicatedServer *bip;
        VirtualServer *pip;
        if (dynamic_cast<DedicatedServer *>(ss)) {
            bip = dynamic_cast<DedicatedServer *>(ss);
            cout << *bip << bip->total_price();
        }
        if (dynamic_cast<VirtualServer *>(ss)) {
            pip = dynamic_cast<VirtualServer *>(ss);
            cout << *pip << pip->total_price();
        }
    }
    return 0;
}