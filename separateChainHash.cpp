#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;

struct node{
    string name;
    int value;
};


class HashTable{
    public:
        bool Switch;
        int pocet, maxPocet;
        const float maxLoad = 0.75;
        const float minLoad = 0.2;
        list<node>* table;
    HashTable(int maxPocet){
        pocet = 0;
        (this->maxPocet) = maxPocet;
        table = new list<node>[maxPocet];
    }
    ~HashTable(){
        delete[] table;
    }
    int hashit(string name, int maxPocet){
        unsigned int offset=1083019949, prime = 8388817;
        unsigned int hash = offset;
        for (int i=0; i < name.length() ;i++){
            unsigned int letter = name[i]; 
            hash = (hash ^ letter);
            hash = (hash * prime);
        }
        return (hash%maxPocet);
    }
    void resizeTable(){
        if (Switch==false){
            maxPocet = (maxPocet<<1);
            list<node>* temp = new list<node>[maxPocet];
            for (int i = 0; i < (maxPocet>>1); i++) {
                for (auto temp2 = (table[i].begin()); (temp2 != (table[i].end())); temp2++) {
                    int tablePlace = hashit((temp2)->name, maxPocet);
                    temp[tablePlace].push_back(*temp2);
                }
            }
            //cout << "Maxpocet is: " << maxPocet <<endl;
            delete[] table;
            table = temp;
        }
        else{
            maxPocet = (maxPocet>>1);
            list<node>* temp = new list<node>[maxPocet];
            for (int i = 0; i < (maxPocet<<1); i++) {
                for (auto temp2 = (table[i].begin()); (temp2 != (table[i].end())); temp2++) {
                    int tablePlace = hashit((temp2)->name, maxPocet);
                    temp[tablePlace].push_back(*temp2);
                }
            }
            //cout << "Maxpocet is: " << maxPocet <<endl;
            delete[] table;
            table = temp;
        }
    }
    void addString(string name, int value){
        int tablePlace = hashit(name, maxPocet);
        node temp;
        temp.name = name;
        temp.value = value;
        table[tablePlace].push_back(temp);
        pocet++;
        //cout << "pocet je: " << pocet <<endl;
        //cout << "maxpocet je: " << maxPocet <<endl;
        double ratio = pocet ;
        ratio = (ratio/ maxPocet);
        //cout << "ratio is :"<< ratio <<endl;
        if (ratio >= maxLoad){
            Switch = false; 
            //cout << "scaling up\n";
            resizeTable();
        }  
    }
    void deleteString(string name) {
        if (findString(name)==false){
            cout << "No such entry: " << name <<endl;
            return;
        }
        int tablePlace = hashit(name, maxPocet);
        for (auto it = table[tablePlace].begin(); it != table[tablePlace].end(); it++) {
            if (it->name == name) {
                table[tablePlace].erase(it);
                break;
            }
        }
        pocet--;
        double ratio = pocet ;
        ratio = (ratio/maxPocet);
        //cout << "ratio is :"<< ratio <<endl;
        if (ratio <= minLoad){
            Switch = true;
            //cout << "scaling down\n"; 
            resizeTable();
        }
    }
    bool findString(string name){
        int tablePlace = hashit(name, maxPocet);
        for(auto temp = table[tablePlace].begin(); (temp != table[tablePlace].end()); temp++){
            if (name == ((temp)->name)){
                return true;
            }
        }
        return false;
    }
    void printTable(){
        for (int i=0; i<maxPocet; i++){
            for (auto temp = table[i].begin(); temp!=table[i].end(); temp++){
                cout << ((temp)->name) << "  " << ((temp)->value) << "  ";
            }
            cout << endl;
        }
    }
};



int main(){
    string input;
    char mode;
    int quit=0, number;
    HashTable hash(20);
    ifstream numero10("NUMBS_10.txt");
    ifstream numero100("NUMBS_100.txt");
    ifstream numero1k("NUMBS_1000.txt");
    ifstream numero10k("NUMBS_10000.txt");
    ifstream numero100k("NUMBS_100000.txt");
    ifstream numero1M("NUMBS_1000000.txt");
    ifstream numero10M("NUMBS_10000000.txt");
    ifstream gringo10("NAMES_10.txt");
    ifstream gringo100("NAMES_100.txt");
    ifstream gringo1k("NAMES_1k.txt");
    ifstream gringo10k("NAMES_10k.txt");
    ifstream gringo100k("NAMES_100k.txt");
    ifstream gringo1M("NAMES_1M.txt");
    ifstream gringo10M("NAMES_10M.txt");
    auto start_time = high_resolution_clock::now();
    /*for (int i = 0; i< 10; i++){
        numero10 >> number;
        gringo10 >> input;
        hash.addNode(input, number);
    }*/
    /*gringo10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        hash.findNode(input);
    }*/
    /*gringo10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 100; i++){
        numero100 >> number;
        gringo100 >> input;
        hash.addNode(input, number);
    }*/
    /*gringo100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        hash.findNode(input);
    }*/
    /*gringo100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 1000; i++){
        numero1k >> number;
        gringo1k >> input;
        hash.addNode(input, number);
    }*/
    /*gringo1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        hash.findNode(input);
    }*/
    /*gringo1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 10000; i++){
        numero10k >> number;
        gringo10k >> input;
        hash.addNode(input, number);
    }*/
    /*gringo10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        hash.findNode(input);
    }*/
    /*gringo10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 100000; i++){
        numero100k >> number;
        gringo100k >> input;
        hash.addNode(input, number);
    }*/
    /*gringo100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        hash.findNode(input);
    }*/
    /*gringo100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i < 1000000; i++){
        numero1M >> number;
        gringo1M >> input;
        hash.addNode(input, number);
    }*/
    /*gringo1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        hash.findNode(input);
    }*/
    /*gringo1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 10000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addNode(input, number);
    }*/
    /*gringo10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        hash.findNode(input);
    }*/
    /*gringo10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        hash.deleteNode(input);
    }*/
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " milliseconds." << endl;
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    /*
    while(quit==0){
        cin >>mode;
        switch(mode){
            case 'a' :{
                cin >> input;
                cin >> number;
                hash.addString(input, number);
                break;
            }
            case 's' :{
                cin >> input;
                cout << hash.findString(input) <<endl;
                break;
            }
            case 'd' :{
                cin >> input;
                hash.deleteString(input);
                break;
            }
            case 'w' :{
                hash.printTable();
                break;
            }
            case 'q': {
                quit = 1;
                break;
            }
            default :{
                cout << "a-ADD/d-DELETE/s-SEARCH/w-WRITEOUT/q-QUIT\n";
                break;
            }
        }
    }*/
    return 0;
}