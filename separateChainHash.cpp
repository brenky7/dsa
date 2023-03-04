#include <iostream>
#include <list>
#include <string>
using namespace std;

class HashTable{
    public:
        bool Switch;
        int pocet, maxPocet;
        const float maxLoad = 0.75;
        const float minLoad = 0.2;
        list<string>* table;
       
    HashTable(int maxPocet){
        pocet = 0;
        (this->maxPocet) = maxPocet;
        table = new list<string>[maxPocet];
    }
    ~HashTable(){
        delete[] table;
    }
    int hashit(string name, int maxPocet){
        int asciiValue=0;
        for (int i=0; i< name.length() ;i++){
            asciiValue+= (name[i]);
        }
        return (asciiValue%maxPocet);
    }
    void resizeTable(){
        if (Switch==false){
            maxPocet = (maxPocet<<1);
            list<string>* temp = new list<string>[maxPocet];
            for (int i = 0; i < (maxPocet>>1); i++) {
                for (auto node = (table[i].begin()); (node != (table[i].end())); node++) {
                    int tablePlace = hashit(*node, maxPocet);
                    temp[tablePlace].push_back(*node);
                }
            }
            //cout << "Maxpocet is: " << maxPocet <<endl;
            delete[] table;
            table = temp;
        }
        else{
            maxPocet = (maxPocet>>1);
            list<string>* temp = new list<string>[maxPocet];
            for (int i = 0; i < (maxPocet<<1); i++) {
                for (auto node = (table[i].begin()); (node != (table[i].end())); node++) {
                    int tablePlace = hashit(*node, maxPocet);
                    temp[tablePlace].push_back(*node);
                }
            }
            //cout << "Maxpocet is: " << maxPocet <<endl;
            delete[] table;
            table = temp;
        }
    }
    void addString(string name){
        int tablePlace = hashit(name, maxPocet);
        table[tablePlace].push_back(name);
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
        string findMy = findString(name);
        if (findMy == "Not found"){
            cout << "No such entry" <<endl;
            return;
        }
        int tablePlace = hashit(name, maxPocet);
        table[tablePlace].remove(name);
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
    string findString(string name){
        int tablePlace = hashit(name, maxPocet);
        for(auto node = table[tablePlace].begin(); (node != table[tablePlace].end()); node++){
            if (name == (*node)){
                return (*node);
            }
        }
        return "Not found";
    }
    void printTable(){
        for (int i=0; i<maxPocet; i++){
            for (auto node = table[i].begin(); node!=table[i].end(); node++){
                cout << (*node) << "  ";
            }
            cout << endl;
        }
    }
};



int main(){
    string input;
    char mode;
    int quit=0;
    HashTable hash(2);
    while(quit==0){
        cin >>mode;
        switch(mode){
            case 'a' :{
                cin >> input;
                hash.addString(input);
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
    }
    return 0;
}