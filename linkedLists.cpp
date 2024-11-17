#include <iostream>
using namespace std;

class Node { // can be a class or struct. a node has two data members:
    public:
        int value; //one with its data value
        Node* next; // one with the pointer to the next node
        // Node* previous; // if it is a doubly linked list, contains pointer to previous node

        Node(int data) { // constructor for node
            this->value = data;
        }

        Node() {}
};

void printList(Node* n) { // when given the head of the linked list
    while(n != NULL) {
        cout << n->value << endl; // prints values of current node, then moves to next node until it is null
        n = n->next;
    }
}

int countNodes(Node* n) { // when given the head of the linked list
    int counter = 0;
    while (n != NULL) { 
        counter++; // adds to counter until next node is null
        n = n->next;
    }
    return counter;
}

int main() {
    Node* head = new Node();
    Node* second = new Node();
    Node* third = new Node();

    head->value = 1;
    head->next = second;

    second->value = 2;
    second->next = third;

    third->value = 3;
    third->next = NULL;
    
    printList(head);
    cout << countNodes(head) << endl;
    return 0;
}