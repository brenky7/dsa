#include <iostream>
#include <string>
#include <vector>
#include <span>

using namespace std;

class Node {
public:
    string factor;
    char variable;
    Node* negative;
    Node* positive;
    Node* parent;
    Node(char Variable){
        variable = Variable;
        negative = NULL;
        positive = NULL;
        parent = NULL;
    }
};

class BDD {
    public:
    int nodeCounter, varCount;
    string function, variables;
    Node* root;
    BDD(){
        nodeCounter = 1;
        root = nullptr;
    }
    void printVariables(){
        for (char pismeno : variables){
            cout << pismeno << endl;
        }
    }
    void bdd_addNodes(Node* node, char variable){
        if (node == nullptr){
            node = new Node(variable);
            cout << node->variable << endl;
        }
    }
    void bdd_create(string bfunction, string order){
        function = bfunction;
        varCount = variables.length();
        variables = order;
        for (char pismeno : variables){
            bdd_addNodes(root, pismeno);
        }
    }
};

int main() {
    BDD strom;
    strom.bdd_create("!AB + ABC + !A!B", "ACB");
    strom.printVariables();
    cout << strom.function << endl;
    //cout<< strom.root->variable << endl;
    return 0;
}

