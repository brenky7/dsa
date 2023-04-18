#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <span>

using namespace std;

class Node {
public:
    string function;
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
    Node* root, *nullNode, *oneNode;
    BDD(){
        nodeCounter = 0;
        root = nullptr;
        nullNode = new Node('0');
        oneNode = new Node('1');
    }
    Node* bdd_addNodes(int height, string function, string order, Node* parent){
        Node* node = new Node(order[order.length()-height]);
        if (height == 0){
            size_t position = function.find('1');
            if (position != string::npos){
                return oneNode;
            }
            else{
                return nullNode;
            }
        }
        node->parent = parent; 
        node->function = function;
        string cut1 = bdd_splitString(function, order[order.length()-height], false);
        string cut2 = bdd_splitString(function, order[order.length()-height], true);
        //cout << cut1 << endl;
        //cout << cut2 << endl;
        node->negative = bdd_addNodes(height-1, cut1, order, node);
        node->positive = bdd_addNodes(height-1, cut2, order, node);
        return node;
    }
    string bdd_splitString(string function, char variable, bool child){
        vector<string> functionCut;
        istringstream ss(function);
        string cut;
        while (getline(ss, cut, '+')){
            functionCut.push_back(cut);
        }
        cut = "";
        for (string& part : functionCut){
            size_t position = part.find(variable);
            if (position != string::npos){
                if (part[position-1] != '!' && child){
                    part[position] = '1';
                    cut += part;
                }
                else if (!child && part[position-1] == '!' && !child){
                    part[position-1] = ' ';
                    part[position] = '1';
                    cut += part;
                }
            }
            else{
                cut += part;
            }
            cut += '+';
        }
        return cut;
    }
    Node* bdd_create(string function, string order){
        root = bdd_addNodes(order.length(), function, order, nullptr);
        return root;
    }
    void printTree(Node* node, int depth = 0){
            if (node == nullptr){
                return;
            }
            printTree(node->positive, depth + 1);
            for (int i = 0; i < depth; i++){
                cout << "           ";
            }
            cout << node->variable << " (" << node->function << ")" << endl;
            printTree(node->negative, depth + 1);
        }
};

int main() {
    BDD strom;
    strom.root =  strom.bdd_create("!AB+ABC+!A!B", "ABC");
    //strom.printVariables();
    cout << strom.function << endl;
    //cout << strom.root->negative->function << endl;
    //cout << strom.root->positive->function << endl;
    strom.printTree(strom.root);
    //cout<< strom.root->variable << endl;
    return 0;
}

