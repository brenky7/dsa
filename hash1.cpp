#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Node{
    public:
        bool used;
        int key;
        string value;
        Node* next;
    Node(string one, int two){
        value = one;
        key = two;
        used = true;
    }
    Node* addNode(Node* table, string name){
        int hashIndex = hashit(name);
        if (table[(hashIndex%5)]==NULL){
            return new Node(name, hashIndex);
        }
        else{
            Node* temp = table[(hashIndex%5)];
            while (temp!=NULL){
                temp = temp->next;
            }
            return new Node(name, hashIndex);
        }
    }
    void printTable(Node* table, int size){
        Node *temp;
        for (int i = 0; i < size; i++){
            temp = table[i];
            while(temp!=NULL){
                cout << temp->key;
                temp==temp->next;
            }
        }
        
    }
};

int hashit(string name){
    int Index=0;
    for (int i=0; i< name.length() ;i++){
        Index+= (name[i]);
    }
    return (Index);
}

int main(){
    string input;
    int output;
    Node *table = new Node[5];
    for (int i = 0; i < 5; i++){
        table[i] = NULL;
    }
    
    printTable(table);
    return 0;
}
