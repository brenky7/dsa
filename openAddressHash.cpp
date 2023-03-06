#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

struct node{
    bool used;
    string name;
    int value;
};

class HashTable {
    public:
        bool Switch = false;
        node* table;
        int maxPocet, pocet;
        const float maxLoad = 0.75;
        const float minLoad = 0.2;
    HashTable(int maxPocet){
        pocet=0;
        (this->maxPocet) = maxPocet;
        table = new node[maxPocet];
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
    string findString(string name){
        int tablePlace = hashit(name, maxPocet);
        if((table[tablePlace].name) == name){
            return (table[tablePlace].name);
        }
        else{
            bool found = false;
            int j=1;
            while((table[tablePlace].used=true)&&((table[tablePlace].name) != name)){
                tablePlace = ((tablePlace + (j*j))% maxPocet);
                j++;
            }
            if((table[tablePlace].name) == name){
                return (table[tablePlace].name);
            }
            return "Not found";
        }
    }
    void resizeTable(){
        if (Switch==false){
            int newMaxPocet = (maxPocet<<1);
            node* temp = new node[newMaxPocet];
            for (int i=0; i < maxPocet;i++){
                int tablePlace = hashit(table[i].name, newMaxPocet);
                if (table[i].used){
                    int j = 1;
                    while (temp[tablePlace].used==true){
                        tablePlace = ((tablePlace + (j*j)) % newMaxPocet);
                        j++;
                    }
                    node temp2;
                    temp2.name = table[i].name;
                    temp2.value = table[i].value;
                    temp2.used = true;
                    temp[tablePlace]=temp2;
                }
            }
            /*for (int i=0; i<(maxPocet>>1);i++){
                int tablePlace = hashit(table[i].name, maxPocet);
                if ((temp[tablePlace].used)==false){
                    temp[tablePlace].name = table[i].name;
                    temp[tablePlace].value = table[i].value;
                    temp[tablePlace].used = true;
                }
                else{
                    bool copied = false;
                    for(int j = (tablePlace+1); j < maxPocet; j++){
                        
                        if ((temp[j].used)==false){
                            temp[j].name =table[i].name;
                            temp[j].value = table[i].value;
                            temp[j].used = true;
                            copied = true;
                            break;
                        }
                    } 
                }
                
            }*/
            maxPocet = newMaxPocet;
            delete[] table;
            table = temp;
            return;
        }
        else{
            int newMaxPocet = (maxPocet>>1);
            node* temp = new node[newMaxPocet];
            for (int i=0; i < maxPocet; i++){
                int tablePlace = hashit(table[i].name, maxPocet);
                if (table[i].used){
                    int j = 1;
                    while (temp[tablePlace].used==true){
                        tablePlace = ((tablePlace + (j*j)) % newMaxPocet);
                        j++;
                    }
                    node temp2;
                    temp2.name = table[i].name;
                    temp2.value = table[i].value;
                    temp2.used = true;
                    temp[tablePlace]=temp2;
                }
            }
            delete[] table;
            table = temp;
            return;
        }
    }
    void addString(string name, int value){
        int tablePlace = hashit(name, maxPocet);
        int j = 1;
        while (table[tablePlace].used==true){
            tablePlace = ((tablePlace + (j*j)) % maxPocet);
            j++;
        }
        node temp2;
        temp2.name = name;
        temp2.value = value;
        temp2.used = true;
        table[tablePlace]=temp2;
        pocet++;
        /*if ((table[tablePlace].used) == false){
            table[tablePlace].name = name;
            table[tablePlace].value = value;
            table[tablePlace].used = true;
            pocet++;
        }
        else{
            bool inserted = false;
            for (int i = (tablePlace+1); i < maxPocet; i++){
                if ((table[i].used)==false){
                    table[i].name = name;
                    table[i].value = value;
                    table[i].used = true;
                    pocet++;
                    inserted = true;
                    break;
                }
            }
            if (inserted == false){
                for (int i = (tablePlace-1); i >=0; i--){
                    if ((table[i].used)==false){
                        table[i].name = name;
                        table[i].value = value;
                        table[i].used = true;
                        pocet++;
                        break;
                    }
                }
            }
        }*/
        double ratio = pocet;
        ratio = (ratio/maxPocet);
        if (ratio >= maxLoad){
            Switch = false;
            resizeTable();
        }
    }
    void deleteString(string name){
        string findMy = findString(name);
        if (findMy == "Not found"){
            cout << "No such entry" <<endl;
            return;
        }
        int tablePlace = hashit(name, maxPocet);
        int j = 1;
        while (table[tablePlace].used==true){
            if ((table[tablePlace].name)==name){
                delete &(table[tablePlace]);
            }
            else{
                tablePlace = ((tablePlace + (j*j)) % maxPocet);
                j++;
            }
        }
        /*if ((table[tablePlace].name) == name){
            table[tablePlace].name = "";
            table[tablePlace].value = 0;
            table[tablePlace].used = false;
        }
        else{
            bool deleted = false;
            for (int i = (tablePlace+1); i < maxPocet; i++){
                if ((table[i].name) == name){
                    table[i].name = "";
                    table[i].value = 0;
                    table[i].used = false;
                    deleted = true;
                    break;
                }
            }
            if (deleted == false){
                for (int i = (tablePlace-1); i >= 0; i--){
                    if ((table[i].name) == name){
                        table[i].name = "";
                        table[i].value = 0;
                        table[i].used = false;
                        deleted = true;
                        break;
                    }
                }
            }
            if (deleted == false){
                cout << ">:(\n";
            }
        }*/
        pocet--;
        double ratio = pocet;
        ratio = (ratio/maxPocet);
        if (ratio <= minLoad){
            Switch = true;
            resizeTable();
        }
    }
    void printTable(){
        for (int i = 0; i < maxPocet; i++){
            cout << table[i].name << " " << table[i].value << endl;
        }
    }

};
int main(){
    string input;
    char mode;
    int quit=0, number;
    HashTable hash(10000000);
    ifstream numero10("NUMBS_10.txt");
    ifstream numero100("NUMBS_100.txt");
    ifstream numero1k("NUMBS_1000.txt");
    ifstream numero100k("NUMBS_100000.txt");
    ifstream numero1M("NUMBS_1000000.txt");
    ifstream numero10M("NUMBS_10000000.txt");
    ifstream gringo10("NAMES_10.txt");
    ifstream gringo100("NAMES_100.txt");
    ifstream gringo1k("NAMES_1k.txt");
    ifstream gringo100k("NAMES_100k.txt");
    ifstream gringo1M("NAMES_1M.txt");
    ifstream gringo10M("NAMES_10M.txt");
    auto start_time = high_resolution_clock::now();
    for (long long i = 0; i< 2000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addString(input, number);
    }
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    for (long long i = 2000000; i< 4000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addString(input, number);
    }
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    for (long long i = 4000000; i< 6000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addString(input, number);
    }
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    for (long long i = 6000000; i< 8000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addString(input, number);
    }
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    for (long long i = 8000000; i< 10000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addString(input, number);
    }
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " milliseconds." << endl;
    cout << hash.maxPocet << endl;
    cout << hash.pocet << endl;
    
    
    
    
    
    
    
    
    /*while(quit==0){
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
    }*/
    return 0;
}

