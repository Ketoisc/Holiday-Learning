#include <iostream>
#include <vector>
#include <string>
using namespace std;

// trie data structure
// like a tree, can store many strings and prefixes
// can efficiently retrieve and store keys in a large dataset
// insertion, search, deletion

struct trieNode {
    trieNode* child[26]; // pointer array for child nodes of each node. 26 letters in alphabet, each index holds a letter/node. nodes will have nodes inside them to act as a tree
    // the array acts like a lookup table. we put the character in the array and just check if it exists, so O(1) lookup
    bool wordEnd; // indicates if a string has ended

    trieNode() {
        wordEnd = false;
        for (int i = 0; i < 26; i++) {
            child[i] = NULL;
        }
    }
};

// inserting a string/key
void insertKey(trieNode* root, const string& key) {
    trieNode* curr = root; // set curr to root node

    for (char c : key) { // iterate across each character in string length
        if (curr->child[c - 'a'] == nullptr) { // if child node does not exist for the current character in the trie
            trieNode* newNode = new trieNode(); // then make a new node for that character, which holds the next letter 
            curr->child[c - 'a'] = newNode; // keep track of new node by inserting it in, forming the tree
        }

        curr = curr->child[c - 'a']; // move curr pointer to the new node/next node to keep traversing the string/trie
    }
    curr->wordEnd = true; // mark end of word after inserted
}

// searching for a string/key
bool searchKey(trieNode* root, const string& key) {
    trieNode* curr = root; // set curr to root node
    for (char c: key) { // iterate across each character in string length
        if (curr->child[c - 'a'] == nullptr) { // if node does not exist for current character being iterated (checking index in array with respect to character)
            return false; // then the key can't exist, return false
        }

        curr = curr->child[c - 'a']; // go to next node that matches
    }
    return curr->wordEnd;
}

bool isEmpty(trieNode* root) { // checks if root has no children
    for (int i = 0; i < 26; i++) {
        if (root->child[i]) {
            return false;
        }
    }
    return true;
}

// function to delete a key/word
trieNode* remove(trieNode* root, string key, int depth = 0) {
    if (!root) { // if there is no root
        return NULL;
    }

    if (key.size() == depth) { // used in recursive calls. if last character is being processed, set wordEnd as false
        if (root->wordEnd) { // remove the word logically but leave the tree intact
            root->wordEnd = false; // word could be a prefix. we delete the word by changing this boolean, so other leaves still exist
        }

        if (isEmpty(root)) { // if the node is empty/has no children (basically useless), then delete the node
            delete root;
            root = NULL;
        }
        return root;
    }

    // if current node is not the last character, then recursively find it
    int index = key[depth] - 'a'; // finds index/character value of current character being processed. key[depth] gives the letter at that position
    root->child[index] = remove(root->child[index], key, depth + 1); // recursively find and process next character, loop until it reaches null or final chcaracter
    if (isEmpty(root) && root->wordEnd == false) { // cleaning up each node after backtracking. if the root does not have any child (its only child got deleted) and it is not the end of another word
        delete root; // ensures no useless nodes are kept after deletion
        root = NULL;
    }
    return root;
}

int main() {
  
    trieNode* root = new trieNode();
    insertKey(root, "and");
    insertKey(root, "ant");
    insertKey(root, "do");
    insertKey(root, "geek");
    insertKey(root, "dad");
    insertKey(root, "ball");


    // search strings
    vector<string> searchKeys = {"do", "gee", "bat"};
    for (string& s : searchKeys) {
        cout << "Key : " << s << "\n";
        if (searchKey(root, s)) 
            cout << "Present\n";
        else 
            cout << "Not Present\n";        
    }
  
    return 0;
}