#include <iostream>
#include <string>
using namespace std;

struct node{
    bool used;
    string name;
    int value;
};

class HashTable {
    public:
        bool Switch;
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
        int asciiValue=0;
        for (int i=0; i < name.length() ;i++){
            asciiValue+= (name[i]);
        }
        return (asciiValue%maxPocet);
    }
    string findString(string name){
        int tablePlace = hashit(name, maxPocet);
        if((table[tablePlace].name) == name){
            return (table[tablePlace].name);
        }
        else{
            bool found = false;
            for(int i=(tablePlace+1); i < maxPocet ; i++){   
                if ((table[i].name) == name){
                    found = true;
                    return table[i].name;
                }
            }
            for(int i=(tablePlace-1); i >=0 ; i--){ 
                if ((table[i].name) == name){
                    found = true;
                    return table[i].name;
                }
            }
            if (found == false){
                return "Not found";
            }
        }
    }
    void resizeTable(){
        if (Switch==false){
            maxPocet = (maxPocet<<1);
            node* temp = new node[maxPocet];
            for (int i=0; i<(maxPocet>>1);i++){
                int tablePlace = hashit(table[i].name, maxPocet);
                if ((temp[tablePlace].used)==false){
                    temp[tablePlace].name = table[i].name;
                    temp[tablePlace].value = tablePlace;
                    temp[tablePlace].used = true;
                }
                else{
                    bool copied = false;
                    for(int j = (tablePlace+1); j < maxPocet; j++){
                        if ((temp[j].used)==false){
                            temp[j].name =table[i].name;
                            temp[j].value = tablePlace;
                            temp[j].used = true;
                            copied = true;
                            break;
                        }
                    }
                    if (copied == false){
                        for(int j = (tablePlace-1); j >=0; j--){
                            if ((temp[j].used)==false){
                                temp[j].name = table[i].name;
                                temp[j].value = tablePlace;
                                temp[j].used = true;
                                copied = true;
                                break;
                            }
                        }
                    }
                    if (copied == false){
                        cout << ">:2\n";
                    }
                }
                
            }
            delete[] table;
            table = temp;
        }
        else{
            maxPocet = (maxPocet>>1);
            node* temp = new node[maxPocet];
            for (int i=0; i<(maxPocet<<1);i++){
                int tablePlace = hashit(table[i].name, maxPocet);
                temp[tablePlace].name = table[i].name;
                temp[tablePlace].value = tablePlace;
                temp[tablePlace].used = true;
            }
            delete[] table;
            table = temp;
        }
    }
    void addString(string name){
        int tablePlace = hashit(name, maxPocet);
        if ((table[tablePlace].used) == false){
            table[tablePlace].name = name;
            table[tablePlace].value = tablePlace;
            table[tablePlace].used = true;
            pocet++;
        }
        else{
            bool inserted = false;
            for (int i = (tablePlace+1); i < maxPocet; i++){
                if ((table[i].used)==false){
                    table[i].name = name;
                    table[i].value = tablePlace;
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
                        table[i].value = tablePlace;
                        table[i].used = true;
                        pocet++;
                        break;
                    }
                }
            }
        }
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
        if ((table[tablePlace].name) == name){
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
        }
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

