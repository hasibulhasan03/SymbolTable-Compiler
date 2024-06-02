#include <iostream>
#include <string>

using namespace std;

class node {
public:
    string name;
    string type;
    node* next;

    node(string n, string t) {
        name = n;
        type = t;
        next = nullptr;
    }
};

class nodeInfo {
public:
    node* head;

    nodeInfo() {
        head = nullptr;
    }
};

class SymbolTable {
private:
    int size;
    nodeInfo** table;

public:
    SymbolTable(int s) {
        size = s;
        table = new nodeInfo*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = new nodeInfo();
        }
    }

    int hashFunction(string name) {
        int sum = 0;
        for (char c : name) {
            sum += c;
        }
        return sum % size;
    }

    void insertSymbol(string name, string type) {
        int index = hashFunction(name);
        node* newNode = new node(name, type);

        if (table[index]->head == nullptr) {
            table[index]->head = newNode;
            cout << name << " Inserted!" << endl;
        } else {
            node* curr = table[index]->head;
            while (curr) {
                if (curr->name == name) {
                    cout << "Symbol already exists!" << endl;
                    return;
                }
                if (curr->next == nullptr) {
                    curr->next = newNode;
                    cout << name << " Inserted!" << endl;
                    return;
                }
                curr = curr->next;
            }
        }
    }

    void displayTable() {
        bool isEmpty = true;
        for (int i = 0; i < size; ++i) {
            cout << i;
            if (table[i]->head) {
                isEmpty = false;
                node* curr = table[i]->head;
                while (curr) {
                    cout << "-> " << curr->name << ", " << curr->type << "/";
                    curr = curr->next;
                }
            } else {
                cout << " No List to be Displayed!";
            }
            cout << endl;
        }
    }
};

int main() {
    int size;
    cout << "Enter Size of Array: ";
    cin >> size;

    SymbolTable *symbolTable = new SymbolTable(size);

    while (true) {
        cout << "\nChoose One of the Options Below:\n";
        cout << "----------------------------------\n";
        cout << "1. Insert\n";
        cout << "2. Display\n";
        cout << "3. Exit\n\n";
        cout << "Your Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter Symbol and Type of Symbol (Separated By a Space): ";
                string symbol, type;
                cin >> symbol >> type;
                symbolTable->insertSymbol(symbol, type);
                break;
            }
            case 2: {
                symbolTable->displayTable();
                break;
            }
            case 3:
                delete symbolTable;
                return 0;
            default:
                cout << "Invalid Choice! Please choose a valid option.\n";
        }
    }

    delete symbolTable;
    return 0;
}
