#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct node{
    bool used;
    int key;
    string value;
    node* next;
};

int hashit( string input, int size){
    int output=0;
    for (int i=0; i< input.length() ;i++){
        output+= (input[i]);
    }
    return (output);
}

int main(){
    string input;
    int output;
    node *arr = new node[5];
    for (int i=0; i<5; i++){
        cin >> input;
        output = hashit(input, 5);
        arr[(output%5)].value = input;
        arr[(output%5)].key = output;
    }
    for (int i=0; i<5; i++){
        cout << arr[i].value << endl;
    }
    return 0;
}
