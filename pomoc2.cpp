#include <iostream>
#include <algorithm>
using namespace std;

class Node{
    public:    
        int key;
        int height;
        Node *lower, *higher;
    /*Node(){
        height=0;
        higher=NULL;
        lower=NULL;
    }*/
    Node(int hodnota){
        height=1;
        key=hodnota;
        lower=NULL;
        higher=NULL;
    }
    int getHeight(Node* node){
        if (node==nullptr){
            return 0;
        }
        else return (node->height);
    }
    int getBalance(Node* node){
        if (node==nullptr) {
            return 0;
        }
        else return (getHeight(node->lower) - getHeight(node->higher));
    }
    void updateHeight(Node* node){
        node->height = (max(getHeight(node->lower), getHeight(node->higher)) + 1);
    }
    void printTree(Node* node, int depth = 0) {
        if (node == nullptr) {
            return;
        }
        printTree(node->higher, depth + 1);
        for (int i = 0; i < depth; i++) {
            cout << "    ";
        }
        cout << node->key << " (" << getBalance(node) << ")" << endl;
        printTree(node->lower, depth + 1);
    }
    Node* leftleftRotate(Node* node){
        Node* temp = node->lower;
        node->lower = temp->higher;
        temp->higher = node;
        node->height = max(getHeight(node->lower), getHeight(node->higher)) + 1;
        temp->height = max(getHeight(temp->lower), getHeight(temp->higher)) + 1;
        return temp;
    }
    Node* rightrightRotate(Node* node){
        Node* temp = node->higher;
        node->higher = temp->lower;
        temp->lower = node;
        node->height = max(getHeight(node->lower), getHeight(node->higher)) + 1;
        temp->height = max(getHeight(temp->lower), getHeight(temp->higher)) + 1;
        return temp;
    }
    Node* leftRotate(Node* node){
        Node* temp = node->higher;
        Node* temp2 = temp->lower;
        temp->lower = node;
        node->higher = temp2;
        node->height = (max(getHeight(node->lower), getHeight(node->higher)) + 1);
        temp->height = (max(getHeight(temp->lower), getHeight(temp->higher)) + 1);
        return temp;
    }
    Node* rightRotate(Node* node){
        Node* temp = node->lower;
        Node* temp2 = temp->higher;
        temp->higher = node;
        node->lower = temp2;
        node->height = (max(getHeight(node->lower), getHeight(node->higher)) + 1);
        temp->height = (max(getHeight(temp->lower), getHeight(temp->higher)) + 1);
        return temp;
    }
    Node* addNode(Node* node, int value){
        if (!node){
            return new Node(value);
        }
        if (value>(node->key)){
            node->higher = addNode(node->higher, value);
        }
        else if (value<(node->key)){
            node->lower = addNode(node->lower, value);
        }
        else{
            return node;
        }
        updateHeight(node);
        int balance = getBalance(node);
        if (balance > 1){
            return leftleftRotate(node);
        }
        if (balance < (-1)){
            return rightrightRotate(node);
        }
        if ((balance > 1)&&(key > (node->lower->key))){
            node->lower = leftRotate(node->lower);
            return rightRotate(node);
        }
        if ((balance < (-1))&&(key < (node->higher->key))){
            node->higher = rightRotate(node->higher);
            return leftRotate(node);
        }
        return node;
    } 
    Node* deleteNode(Node* node, int value){
        if (node==NULL){
            return node;
        }
        if (value<(node->key)){
            node->lower = deleteNode(node->lower, value);
        } 
        else if (value > node->key){
            node->higher = deleteNode(node->higher, value);
        } 
        else{
            if ((node->lower==NULL)&&(node->higher==NULL)){
                delete node;
                node = NULL;
            }
            else if (node->lower==NULL){
                Node* temp = node;
                node = node->higher;
                delete temp;
            } 
            else if (node->higher==NULL){
                Node* temp = node;
                node = node->lower;
                delete temp;
            }
            else{
                Node* temp = node->higher;
                while (temp->lower!=NULL){
                    temp=temp->lower;
                }
                node->key = temp->key;
                node->higher = deleteNode(node->higher, temp->key);
            }
        }
        if (node==NULL) {
            return node;
        }
        updateHeight(node);
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->lower) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->lower) < 0) {
            node->lower = leftRotate(node->lower);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->higher) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->higher) > 0) {
            node->higher = rightRotate(node->higher);
            return leftRotate(node);
        }
        return node;
    }
    Node* findNode(Node* node, int value){
        if ((!node)||((node->key)==value)){
            return node;
        }
        if (value < node->key){
            return findNode(node->lower, value);
        } 
        else{
            return findNode(node->higher, value);
        }
    }
};

int main() {
    int number, zastav=0;
    char vstup;
    Node *koren = NULL;
    while(zastav==0){
        cin >>vstup;
        switch(vstup){
            case 'a' :{
                cout << "Enter number \n";
                cin >> number;
                koren = (koren)->addNode(koren, number);
                break;
            }
            case 'd' :{
                cout << "Enter number \n";
                cin >> number;
                koren->deleteNode(koren, number);
                break;
            }
            case 's' :{
                cout << "Enter number \n";
                cin >> number;
                Node *temp = koren->findNode(koren, number);
                cout << "Height: " << temp->height << "\n";
                break;
            }
            case 'w' :{
                koren->printTree(koren);
                /*cout << koren->key << "\n";
                cout << (koren->higher)->key << "\n";
                cout << (koren->lower)->key << "\n";
                cout << (koren->lower->lower)->key << "\n";
                cout << (koren->lower->higher)->key << "\n";
                cout << (koren->higher->lower)->key << "\n";
                cout << (koren->higher->higher)->key << "\n";*/
                break;
            }
            case 'q' :{
                zastav=1;
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