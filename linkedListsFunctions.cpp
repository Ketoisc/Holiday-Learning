#include <iostream>
using namespace std;

// struct for node in linked list
struct list {
    int item;
    list* next;
};

// SEARCHING IN A LIST
// o complexity: worst case is O(n), if the target node is at the end of the list or does not exist, where n is the number of nodes in the list.
// the function would need to check every node once, so O(n)
list* search_list(list* l, int x) { // recursive method to search for an item x in the list
    if (l == NULL) { // if list is empty, return empty list
        return NULL;
    }

    if (l->item == x) { // if current node's item is x, return that node l
        return l;
    }
    else {
        return search_list(l->next, x); // else search again
    }
}

// INSERTION IN A LIST (insert at beginning of list)
// o complexity of O(1). executes a fixed number of operations regardless of list size. only done at the head of the list
void insert_list(list** startOfList, int x) {
    list* newNode = new list(); // makes new node to be inserted
    newNode->item = x; // sets values
    newNode->next = *startOfList; // sets the next data member/second node in the list to be the pointer to the initial start of list
    *startOfList = newNode; // copies newNode to the place pointed to by startOfList to maintain access to the head of the list
}

// FINDING PREDECESSOR - DELETION FROM A LIST
// need to find predecessor of the item to be deleted
// find predecessor first, then change its "next" data member to remove from linked list

// o complexity of O(n). could be that the target node is at the end of the list or does not exist, requiring a linear search to find the predecessor
list* predecessor_list(list* l, int x) {
    if ((l == NULL) || (l->next == NULL)) {
        return NULL;
    }

    if ((l->next)->item == x) {
        return l;
    }
    else {
        return predecessor_list(l->next, x);
    }
}

// DELETION FROM A LIST
// uses search_list() and predecessor_list() which both have o complexity of O(n), which is sequential and not nested
// therefore o complexity of deletion is O(n)
void delete_list(list** l, int x) {
    list* node; // item pointer
    list* pred; // predecessor pointer

    node = search_list(*l, x); // find the node to be deleted

    if (node != NULL) { // if node exists
        pred = predecessor_list(*l, x); // find its predecessor
        if (pred == NULL) { // if the predecessor is empty (aka if the node to be deleted is the first node)
            *l = node->next; // ignore both the predecessor and the node. set the list to begin at the node after the node to be deleted
        }
        else 
        {
            pred->next = node->next; // if predecessor exists, make the predecessor point to the next node pointed to by the node to be deleted
        }
        delete node;
    }

}