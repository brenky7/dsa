#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

const float maxLoad = 0.75;
const float minLoad = 0.2;
const float chokePoint = 0.3;

class node{
    public:
        string name;
        int value;
    node(string inputName, int inputValue){
        this->name = inputName;
        this->value = inputValue;
    }
    node (){
        name = "deleted";
    }
};

class HashTable {
    public:
        int tableSize;
        int tableChokePoint;
        int elementCount; 
        node** table;
    HashTable(int inputSize){
        tableSize = inputSize;
        table = new node*[tableSize];
        for (int i = 0; i < inputSize; i++){
            table[i] = nullptr;
        }
        elementCount = 0;
        double temp = (chokePoint*tableSize);
        tableChokePoint = round(temp);
    }
    int hashit(string name){
        unsigned int offset=8388817, prime = 4194419;
        unsigned int hash = offset;
        for (int i=0; i < name.length() ;i++){
            unsigned int letter = name[i]; 
            hash = (hash ^ letter);
            hash = (hash * prime);
        }
        return (hash);
    }
    void upScaleTable(){
        int newTableSize = (tableSize*2);
        node** tempTable = new node*[newTableSize];
        for (int i = 0; i < newTableSize; i++){
            tempTable[i] = nullptr;
        }
        for (int i = 0; i < tableSize; i++){
            if ((table[i]!=nullptr)&&((table[i]->name) != "deleted")){
                unsigned int index = hashit(table[i]->name);
                if (tempTable[(index%newTableSize)]==nullptr){
                    tempTable[(index%newTableSize)] = new node(table[i]->name, table[i]->value);
                }
                else{
                    unsigned int j = 1;
                    while (tempTable[(index%newTableSize)]!=nullptr){
                        index = (index + (j*j));
                        j++;
                        if ( j >  chokePoint){
                            unsigned int k = 1;
                            while (tempTable[(index%newTableSize)]!=nullptr){
                                index  = (index + k);
                                k++;
                            }    
                        }       
                    }
                    tempTable[(index%newTableSize)]= new node(table[i]->name, table[i]->value);
                }
            }
        }
        delete[] table;
        table = tempTable;
        tableSize = newTableSize;
        return;
    }
    void downScaleTable(){
        int newTableSize = (tableSize/2);
        node** tempTable = new node*[newTableSize];
        for (int i = 0; i < newTableSize; i++){
            tempTable[i] = nullptr;
        }
        for (int i = 0; i < tableSize; i++){
            if ((table[i]!=nullptr)&&((table[i]->name) != "deleted")){
                unsigned int index = hashit(table[i]->name);
                if (tempTable[(index%newTableSize)]==nullptr){
                    tempTable[(index%newTableSize)] = new node(table[i]->name, table[i]->value);
                }
                else{
                    unsigned int j = 1;
                    while (tempTable[(index%newTableSize)]!=nullptr){
                        index = (index + (j*j));
                        j++;
                        if ( j >  chokePoint){
                            unsigned int k = 1;
                            while (tempTable[(index%newTableSize)]!=nullptr){
                                index  = (index + k);
                                k++;
                            }    
                        }       
                    }
                    tempTable[(index%newTableSize)]= new node(table[i]->name, table[i]->value);
                }
            }
        }
        delete[] table;
        table = tempTable;
        tableSize = newTableSize;
        return;
    }
    void addNode(string name, int value){
        unsigned int index = hashit(name);
        if (table[(index%tableSize)]==nullptr){
            table[(index%tableSize)] = new node(name, value);
        }
        else{
            unsigned int j = 1;
            while (table[(index%tableSize)]!=nullptr){
                index = (index + (j*j));
                j++;
                if ( j >  chokePoint){
                    unsigned int k = 1;
                    while (table[(index%tableSize)]!=nullptr){
                        index  = (index + k);
                        k++;
                    }    
                }
            }
            table[(index%tableSize)]= new node(name, value);
        }
        elementCount++;
        double ratio = elementCount ;
        ratio = (ratio / tableSize);
        if (ratio >= maxLoad){
            //cout << "scaling up\n";
            upScaleTable();
        }
        return;
    }
    bool findNode(string name){
        unsigned int index = hashit(name);
        unsigned int j = 1;
        if (table[(index%tableSize)]->name==name){
            return true;
        }
        else{
            while ((table[(index%tableSize)]!=nullptr)&&(table[(index%tableSize)]->name!=name)){
                index = (index + (j*j));
                j++;
                if ( j >  chokePoint){
                    unsigned int k = 1;
                    while ((table[(index%tableSize)]!=nullptr)&&(table[(index%tableSize)]->name!=name)){
                        index  = (index + k);
                        k++;
                    }    
                }
            }
        }
        if (table[(index%tableSize)]->name == name){
            return true;
        }
        else{
            return false;
        }
    }
    bool deleteNode(string name){
        unsigned int index = hashit(name);
        unsigned int j = 1;
        if (table[(index%tableSize)]->name==name){
            delete table[(index%tableSize)];
            table[(index%tableSize)] = new node();
            elementCount--;
            double ratio = elementCount;
            ratio = (ratio / tableSize);
            if (ratio <= minLoad){
                //cout << "scaledown\n";
                downScaleTable();
            }
            return true;
        }
        else{
            while ((table[(index%tableSize)]!=nullptr)&&(table[(index%tableSize)]->name!=name)){
                index = (index + (j*j));
                j++;
                if ( j >  chokePoint){
                    unsigned int k = 1;
                    while ((table[(index%tableSize)]!=nullptr)&&(table[(index%tableSize)]->name!=name)){
                        //cout << "zapajam linear\n";
                        index  = (index + k);
                        k++;
                    }    
                }
            }
        }
        if (table[(index%tableSize)]->name == name){
            delete table[(index%tableSize)];
            table[(index%tableSize)] = new node();
            elementCount--;
            double ratio = elementCount;
            ratio = (ratio / tableSize);
            if (ratio <= minLoad){
                //cout << "scaledown\n";
                downScaleTable();
            }
            return true;
        }
        else{
            return false;
        }
    }
};



int main(){
    string input;
    int number;
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
    }
    gringo10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        hash.findNode(input);
    }
    gringo10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 100; i++){
        numero100 >> number;
        gringo100 >> input;
        hash.addNode(input, number);
    }
    gringo100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        hash.findNode(input);
    }
    gringo100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 1000; i++){
        numero1k >> number;
        gringo1k >> input;
        hash.addNode(input, number);
    }
    gringo1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        hash.findNode(input);
    }
    gringo1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 10000; i++){
        numero10k >> number;
        gringo10k >> input;
        hash.addNode(input, number);
    }
    gringo10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        hash.findNode(input);
    }
    gringo10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i< 100000; i++){
        numero100k >> number;
        gringo100k >> input;
        hash.addNode(input, number);
    }
    gringo100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        hash.findNode(input);
    }
    gringo100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        hash.deleteNode(input);
    }*/
    /*for (int i = 0; i < 1000000; i++){
        numero1M >> number;
        gringo1M >> input;
        hash.addNode(input, number);
    }
    gringo1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        hash.findNode(input);
    }
    gringo1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        hash.deleteNode(input);
    }*/
    for (int i = 0; i< 10000000; i++){
        numero10M >> number;
        gringo10M >> input;
        hash.addNode(input, number);
    }
    gringo10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        hash.findNode(input);
    }
    gringo10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        hash.deleteNode(input);
    }
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " milliseconds." << endl;
    cout << "number of elements: " << hash.elementCount << endl;
    return 0;
}

