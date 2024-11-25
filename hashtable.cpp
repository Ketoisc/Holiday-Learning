#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

// Hashtables are a very practical way to maintain a dictionary
// looking an item up in an array takes constant time once you have its index

// Essentially an array of keys (values). Keys could be strings, so we need to convert them into integers. 
// Then you take this integer value % (m, the size of array) to get an index number to insert into the array.
// Hash function is a function that translates keys to array indices

// It is ideal for m to be a prime number, as the elements will be more uniformly distributed since elements 
// would not be inserted into the table as evenly, thus having less collisions

struct node {
    const char* key;
    const char* value;
    node* next;
};


void setNode(node* node, const char* key, const char* value) {
        node->key = key;
        node->next = NULL;
        node->value = value;
        return;
}

struct hashMap {
    int numElements;
    int capacity;
    node** array;
};

// initialising values. numelements should be prime
void initialiseHashMap(hashMap* map) {
    map->capacity = 79;
    map->numElements = 0;

    map->array = new node*[map->capacity];
    for (int i = 0; i < map->capacity; i++) {
        map->array[i] = NULL; // initialise each element to NULL
    }
    return;
}

// assuming characters are from 'a' to 'z', no input sanitation
int hashFunction (hashMap* map, const char* key) {
    int index;
    int sum = 0;
    int length = strlen(key);

    for (int i = 0; i < length; i++) { // formula from adm
        sum += (key[i] - 'a' + 1) * pow(26,(length - i - 1));
    }
    return (sum % map->capacity);
}

// insert a node with key and value
void insert(hashMap* map, const char* key, const char* value) {
    int index = hashFunction(map, key); // find array index by hashing
    node* newNode = new node;
    setNode(newNode, key, value); // create node

    if (map->array[index] == NULL) { // if head of list is empty, insert
        map->array[index] = newNode;
    }

    else {
        newNode->next = map->array[index]; // else, insert at the head of the list (order does not matter)
        map->array[index] = newNode;
    }
    return;
}

// given a key, delete the node
void deleteKey(hashMap* map, const char* key) {
    int index = hashFunction(map, key);
    node* prevNode = NULL;
    node* currNode = map->array[index];

    while (currNode != NULL) { // while list is not empty
        if (strcmp(currNode->key, key) == 0) { // if key is found
            if (currNode == map->array[index]) { // if node is at the head of the list
                map->array[index] = currNode->next; // head of list now points to next node, so the node is lost/unlinked from list
            }
            else { // if node is not at head of list
                prevNode->next = currNode->next; // previous node now points to the node after the one being deleted to unlink from list
            }
            delete currNode;
            break;
        }

        // go to next node for checking
        prevNode = currNode;
        currNode = currNode->next;
    }
    return;
}

// given a key, find its value
const char* search(hashMap* map, const char* key) {
    int index = hashFunction(map, key);
    node* currNode = map->array[index];

    while (currNode != NULL) { // while there are still nodes in the list
        if (strcmp(currNode->key, key) == 0) {
            return currNode->value; // keep cycling through list to find and return corresponding value to the key
        }
        currNode = currNode->next;
    }

    // if key not found, search reaches the end of list
    return "Key not found\n";
}

int main() {
    hashMap* map = new hashMap;
    initialiseHashMap(map);

    insert(map, "maths", "Brooke");
    insert(map, "science", "Maggie");
    insert(map, "english", "Josh");

    cout << search(map, "english") << endl;
    cout << search(map, "science") << endl;
    cout << search(map, "maths") << endl;

    cout << search(map, "not here") << endl;

    deleteKey(map, "maths");

    cout << search(map, "maths") << endl;
    return 0;

}