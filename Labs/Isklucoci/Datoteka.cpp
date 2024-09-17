#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    //Your code
    std::ifstream dat("C:\\Users\\Teodora\\CLionProjects\\SP_2023\\OOP\\Labs\\Isklucoci\\text.txt");
    if(!dat.is_open()){
        std::cout<<"Error opening the file"<<std::endl;
        return -1;
    }
    int lower=0;
    int upper=0;
    int total=0;
    char c;
    while(dat.get(c) && c!='#'){
        if(isalpha(c)){
            total++;
            if(islower(c)){
                lower++;
            }
            if(isupper(c)){
                upper++;
            }
        }
    }
    dat.close();

    std::cout << std::fixed << std::setprecision(4);
    std::cout<<upper/(float )total<<std::endl;
    std::cout<<lower/(float)total<<std::endl;
    return 0;
}