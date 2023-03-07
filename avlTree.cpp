#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

struct Node{
    int key;
    int height;
    string name;
    Node *lower, *higher;
}*groot;

class AVLTree{
    public:    
        AVLTree(){
            groot = NULL;
        }
        Node* destructTree(Node** node){
            if (*(node)==NULL){
                return NULL;
            } 
            destructTree(&(*node)->lower);
            destructTree(&(*node)->higher);
            delete *(node);
            return NULL;
    }
        int getHeight(Node* node){
            if (node==NULL){
                return 0;
            }
            else return (node->height);
        }
        int getBalance(Node* node){
            if (node==NULL) {
                return 0;
            }
            else return (getHeight(node->lower) - getHeight(node->higher));
        }
        void updateHeight(Node* node){
            if (node!=NULL){
                node->height = (max(getHeight(node->lower), getHeight(node->higher)) + 1);
            }
        }
        void printTree(Node* node, int depth = 0) {
            if (node == NULL) {
                return;
            }
            printTree(node->higher, depth + 1);
            for (int i = 0; i < depth; i++) {
                cout << "    ";
            }
            cout << node->key << " (" << node->name << ")" << endl;
            printTree(node->lower, depth + 1);
        }
    Node* leftleftRotate(Node** node){
        //cout <<"rotLL\n";
        Node *temp = ((*node)->lower);
        ((*node)->lower) = (temp->higher);
        (temp->higher) = (*node);
        updateHeight(*node);
        updateHeight(temp);
        return temp;
    }
    Node* rightrightRotate(Node** node){
        //cout <<"rotRR\n";
        Node *temp = ((*node)->higher);
        (*node)->higher = temp->lower;
        temp->lower = (*node);
        updateHeight(*node);
        updateHeight(temp);
        return temp;
    }
    Node* leftRotate(Node* node){
        //cout <<"rotL\n";
        Node* temp = node->higher;
        Node* temp2 = temp->lower;
        temp->lower = node;
        node->higher = temp2;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }
    Node* rightRotate(Node* node){
        //cout <<"rotR\n";
        Node* temp = node->lower;
        Node* temp2 = temp->higher;
        temp->higher = node;
        node->lower = temp2;
        updateHeight(node);
        updateHeight(temp);
        return temp;
    }
    Node *balanceNode(Node *node) {
        if (node == NULL) {
            return node;
        }
        int bf = getBalance(node);
        if (bf > 1) {
            if (getBalance(node->lower) < 0) {
                node->lower = leftRotate(node->lower);
            }
            return rightRotate(node);
        }
        else if (bf < -1) {
            if (getBalance(node->higher) > 0) {
                node->higher = rightRotate(node->higher);
            }
            return leftRotate(node);
        }
        return node;
    }
    Node* addNode(Node* node, int value, string meno){
        if (!(node)){
            node =  new Node;
            node->lower = NULL;
            node->higher = NULL;
            node->name = meno;
            node->key = value;
        }
        if (value>((node)->key)){
            (node)->higher = addNode(((node)->higher), value, meno);
        }
        else if (value<((node)->key)){
            (node)->lower = addNode(((node)->lower), value, meno);
        }
        else{
            return (node);
        }
        updateHeight(node);
        return balanceNode(node);
    }
    /*Node* extraBalans(Node** node, int value){
        if (value>((*node)->key)){
            updateHeight(*node);
            (*node)->higher = addNode((&(*node)->higher), value);
        }
        else if (value<((*node)->key)){
            updateHeight(*node);
            (*node)->lower = addNode((&(*node)->lower), value);
        }
        else{
            updateHeight(*node);
            int balance = getBalance(*node);
            if ((balance > 1)&&(value < (((*node)->lower)->key))){
                return leftleftRotate(&(*node));
            }
            if ((balance < (-1))&&(value > (((*node)->higher)->key))){
                return rightrightRotate(&(*node));
            }
            if ((balance > 1)&&(value > (((*node)->lower)->key))){
                (*node)->lower = leftRotate(&((*node)->lower));
                return rightRotate(&(*node));
            }
            if ((balance < (-1))&&(value < (((*node)->higher)->key))){
                (*node)->higher = rightRotate(&((*node)->higher));
                return leftRotate(&(*node));
            }
        }
        return (*node);
    } */
    Node* deleteNode(Node** node, int value){
        if (!(*node)){
            return (*node);
        }
        if (value < ((*node)->key)){
            ((*node)->lower) = deleteNode(&((*node)->lower), value);
        } 
        else if (value > (((*node)->key))){
            ((*node)->higher) = deleteNode(&((*node)->higher), value);
        } 
        else{
            if ((((*node)->lower) == NULL)&&(((*node)->higher) == NULL)){
                delete (*node);
                (*node)=NULL;
            }
            else if ((((*node)->lower) == NULL)&&(((*node)->higher) != NULL)){
                Node* temp = (*node);
                (*node) = ((*node)->higher);
                delete temp;
                temp = NULL;
                return (*node);
            } 
            else if ((((*node)->higher) == NULL)&&(((*node)->lower) != NULL)){
                Node* temp = (*node);
                (*node) = ((*node)->lower);
                delete temp;
                temp = NULL;
                return (*node);
            }
            else{
                Node* temp = ((*node)->higher);
                while ((temp->lower)!=NULL){
                    temp=(temp->lower);
                }
                (*node)->key = (temp->key);
                ((*node)->higher) = deleteNode(&((*node)->higher), (temp->key));
            }
        }
        if ((*node)==NULL) {
            return (*node);
        }
        updateHeight(*node);
        return balanceNode(*node);
    }
    Node* findNode(Node* node, int value){
        if ((!node)||((node->key)==value)){
            return node;
        }
        if ((value < node->key)&&((node->lower)!=NULL)){
            return findNode(node->lower, value);
        } 
        else if ((value > node->key)&&((node->higher)!=NULL)){
            return findNode(node->higher, value);
        }
        else{
            cout << "No such node\n";
            return NULL;
        }
    }
};

int main(){
    int number, zastav=0;
    char vstup;
    string meno;
    AVLTree *koren = NULL;
    ifstream numero10("NUMBS_10.txt");
    ifstream numero100("NUMBS_100.txt");
    ifstream numero1k("NUMBS_1000.txt");
    ifstream numero100k("NUMBS_100000.txt");
    ifstream numero1M("NUMBS_1000000.txt");
    ifstream numero10M("NUMBS_10000000.txt");
    ifstream gringo10("NAMES_10.txt");
    ifstream gringo100("NAMES_10.txt");
    ifstream gringo1k("NAMES_10.txt");
    ifstream gringo100k("NAMES_10.txt");
    ifstream gringo1M("NAMES_10.txt");
    ifstream gringo10M("NAMES_10.txt");
    auto start_time = high_resolution_clock::now();
    for (int i = 0; i< 10000000; i++){
        numero10M >> number;
        gringo10M >> meno;
        groot = koren->addNode(groot, number, meno);
    }
    cout << groot->key << endl;
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " milliseconds." << endl;
    groot = koren->destructTree(&groot);
    /*while(zastav==0){
        cin >>vstup;
        switch(vstup){
            case 'a' :{
                cout << "Enter number \n";
                cin >> number;
                koren = (koren)->addNode(&koren, number);
                koren = (koren)->extraBalans(&koren, number);
                break;
            }
            case 'd' :{
                cout << "Enter number \n";
                cin >> number;
                koren->deleteNode(&koren, number);
                break;
            }
            case 's' :{
                cout << "Enter number \n";
                cin >> number;
                Node *temp = koren->findNode(koren, number);
                if (temp!=NULL){
                    cout << "Height: " << temp->height << "\n";
                }
                break;
            }
            case 'w' :{
                koren->printTree(koren);
                break;
            }
            case 'q' :{
                koren = koren->destructTree(&koren);
                zastav=1;
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