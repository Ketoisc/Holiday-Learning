#include <iostream>
#include <string>
using namespace std;

// Hashtables are a very practical way to maintain a dictionary
// looking an item up in an array takes constant time once you have its index

// Essentially an array of keys (values). Keys could be strings, so we need to convert them into integers. 
// Then you take this integer value % (m, the size of array) to get an index number to insert into the array.
// Hash function is a function that translates keys to array indices

// It is ideal for m to be a prime number, as the elements will be more uniformly distributed since elements 
// would not be inserted into the table as evenly, thus having less collisions

struct node {
    char* key;
    char* value;
    node* next;
};


void setNode(node* node, char* key, char* value) {
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

void initialiseHashMap(hashMap* map) {
    map->capacity = 79;
    map->numElements = 0;

    map->array = new node*[sizeof(node*) * map->capacity];
    return;
}

// assuming characters are from 'a' to 'z', no input sanitation
int hashFunction (hashMap* map, char* key) {
    int index;
    int sum = 0;

    for (int i = 0; i < strlen(key); i++) {
        sum += (key[i] - 'a' + 1) * 26^(strlen(key) - i - 1);
    }
    return (sum % map->capacity);
}

void insert(hashMap* map, char* key, char* value) {
    int index = hashFunction(map, key);
    node* newNode = new node;
    setNode(newNode, key, value);

    if (map->array[index] == NULL) {
        map->array[index] = newNode;
    }

    else {
        newNode->next = map->array[index];
        map->array[index] = newNode;
    }
    return;
}

void deleteKey(hashMap* map, char* key) {
    int index = hashFunction(map, key);
    
}