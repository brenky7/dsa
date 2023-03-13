#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>
using namespace std;
using namespace chrono;

struct Node{
    int key;
    string name;
    Node *lower, *higher, *parent;
}*root;

class SplayTree{
    public:     
        SplayTree(){
            root = nullptr;
        }
    Node* newNode(int key, string name){
        Node* node = new Node;
        node->key = key;
        node->name = name;
        node->lower = nullptr;
        node->higher = nullptr;
        node->parent = nullptr;
        return node;
    }
    Node* rightRotate(Node* myNode){
        Node* temp = myNode->lower;
        myNode->lower = temp->higher;
        if(temp->higher != nullptr){
            temp->higher->parent = myNode;
        }
        temp->parent = myNode->parent;
        if (myNode->parent == nullptr){
            root = temp;
        }
        else if(myNode == myNode->parent->lower){
            myNode->parent->lower = temp;
        }
        else if (myNode == myNode->parent->higher){
            myNode->parent->higher = temp;
        }
        if (temp != nullptr){
            temp->higher = myNode;
            myNode->parent = temp;
        }
        return temp;
    }
    Node* leftRotate(Node* myNode){
        Node* temp = myNode->higher;
        myNode->higher = temp->lower;
        if (temp->lower != nullptr){
            temp->lower->parent = myNode;
        }
        temp->parent = myNode->parent;
        if (myNode->parent == nullptr){
            root = temp;
        }
        else if(myNode == myNode->parent->lower){
            myNode->parent->lower = temp;
        }
        else if(myNode == myNode->parent->higher){
            myNode->parent->higher = temp;
        }
        if (temp != nullptr){
            temp->lower = myNode;
            myNode->parent = temp;
        }
        return temp;
    }
    Node* splayNode(Node* myNode, Node* rootNode){
        if (myNode->parent == rootNode){
            return myNode;
        }
        while(myNode->parent != rootNode){
            Node* grandParent = myNode->parent->parent;
            Node* Parent = myNode->parent;
            if (grandParent == rootNode){
                if (myNode == Parent->lower){
                    rightRotate(Parent);
                }
                else if (myNode == Parent->higher){
                    leftRotate(Parent);
                }   
            }
            else if((myNode == Parent->lower)&&(Parent == grandParent->lower)){
                grandParent = rightRotate(grandParent);
                Parent = rightRotate(Parent);
            }
            else if((myNode == Parent->higher)&&(Parent == grandParent->higher)){
                grandParent = leftRotate(grandParent);
                Parent = leftRotate(Parent);
            }
            else if((myNode == Parent->lower)&&(Parent == grandParent->higher)){
                Parent = rightRotate(Parent);
               grandParent = leftRotate(grandParent);
            }
            else if((myNode == Parent->higher)&&(Parent == grandParent->lower)){
                Parent = leftRotate(Parent);
                grandParent = rightRotate(grandParent);
            }
        }
        return myNode;
    }
    Node* addNode(Node* myNode, int key, string name){
        if (myNode == nullptr){
            //cout << "add1\n";
            root = newNode(key, name);
            return root;
        }
        Node* temp = myNode;
        while(true){
            if(temp->key == key){
                return root;
            }
            else if(temp->key > key){
                if(temp->lower == nullptr){
                    //cout << "add2\n";
                    temp->lower = newNode(key, name);
                    temp->lower->parent = temp;
                    root = splayNode(temp->lower, nullptr);
                    return root;
                }
                else{
                    temp = temp->lower;
                }
            }
            else if(temp->key < key){
                if (temp->higher == nullptr){
                    //cout << "add3\n";
                    temp->higher = newNode(key, name);
                    temp->higher->parent = temp;
                    root = splayNode(temp->higher, nullptr);
                    return root;
                }
                else {
                    temp = temp->higher;
                }
            }
        }
    }
    bool findNode(Node* myNode, int key){
        if (!myNode){
            return false;
        }
        if (myNode->key == key){
            splayNode(myNode, nullptr);
            return true;
        }
        else if (myNode->key > key){
            return findNode(myNode->lower, key);
        }
        else if (myNode->key < key){
            return findNode(myNode->higher, key);
        }
    }
    Node* deleteNode(Node* myNode, int key){
        //cout << findNode(myNode, key) << endl;
        if (myNode == nullptr){
            return nullptr;
        }
        else{
            findNode(root, key);
        }
        if((root->lower == nullptr)&&(root->higher == nullptr)){
            delete root;
            return nullptr;
        }
        else if((root->lower == nullptr)&&(root->higher != nullptr)){
            Node* temp = root;
            root = root->higher;
            delete temp;
            root->parent = nullptr;
            return root;
        }
        else if((root->lower != nullptr)&&(root->higher == nullptr)){
            Node* temp = root;
            root = root->lower;
            delete temp;
            root->parent = nullptr;
            return root;
        }
        else if ((root->lower != nullptr)&&(root->higher != nullptr)){
            Node* temp = root->lower;
            while (temp->higher != nullptr){
                temp = temp->higher;
            }
            //cout << temp->key << temp->parent->key << endl;
            if (root->lower != temp){
                root->lower = splayNode(temp,root);
            }
            temp->higher = root->higher;
            root->higher->parent = temp;
            Node* temp2 = root;
            root = root->lower;
            delete temp2;
            root->parent = nullptr;
            return root;
        }
    }
    void printSplayTree(Node* myNode, int depth = 0){
        if (myNode != nullptr){
            printSplayTree(myNode->higher, depth+1);
            cout << setw(4*depth) << "";
            cout << myNode->key << "(" << myNode->name << ")" << endl;
            printSplayTree(myNode->lower, depth+1);
        }
    }
};

int main(){
    int number, zastav=0;
    string name;
    char vstup;
    SplayTree *myTree = nullptr;
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
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero10.seekg(0);
    for (int i = 0; i< 10; i++){
        gringo10 >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i< 100; i++){
        numero100 >> number;
        gringo100 >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero100.seekg(0);
    for (int i = 0; i< 100; i++){
        gringo100 >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i< 1000; i++){
        numero1k >> number;
        gringo1k >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero1k.seekg(0);
    for (int i = 0; i< 1000; i++){
        gringo1k >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i< 10000; i++){
        numero10k >> number;
        gringo10k >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero10k.seekg(0);
    for (int i = 0; i< 10000; i++){
        gringo10k >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i< 100000; i++){
        numero100k >> number;
        gringo100k >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero100k.seekg(0);
    for (int i = 0; i< 100000; i++){
        gringo100k >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i < 1000000; i++){
        numero1M >> number;
        gringo1M >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero1M.seekg(0);
    for (int i = 0; i< 1000000; i++){
        gringo1M >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    /*for (int i = 0; i< 10000000; i++){
        numero10M >> number;
        gringo10M >> input;
        groot = myTree->addNode(groot, number, meno);
    }*/
    /*numero10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        myTree->findNode(groot, number);
    }*/
    /*numero10M.seekg(0);
    for (int i = 0; i< 10000000; i++){
        gringo10M >> input;
        groot = myTree->deleteNode(groot, number);
    }*/
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();
    //myTree->printSplayTree(root);
    cout << "Time taken: " << duration << " milliseconds." << endl;
    /*while(zastav==0){
        cin >>vstup;
        switch(vstup){
            case 'a' :{
                cout << "Enter number \n";
                cin >> number;
                cout << "Enter data \n";
                cin >> name;
                root = myTree->addNode(root, number, name);
                break;
            }
            case 's' :{
                cout << "Enter number \n";
                cin >> number;
                cout << myTree->findNode(root, number) << endl;
                break;
            }
            case 'd' :{
                cout << "Enter number \n";
                cin >> number;
                root = myTree->deleteNode(root, number);
                break;
            }
            case 'w' :{
                myTree->printSplayTree(root);
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
    }*/
    return 0;
}


