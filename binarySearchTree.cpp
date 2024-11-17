#include <iostream>
using namespace std;

// binary trees can be balanced or skewed (eg only nodes on the right side)

struct tree {
    int item;
    tree* parent;
    tree* left;
    tree *right;
};

// operations for binary trees are
// searching, traversal, insertion, deletion

//SEARCHING
// o complexity of O(log n) or O(height of tree). binary searching means to cut in half for each search
tree* search_tree(tree* l, int x) { // parameters are root of tree, and value being searched for
    if (l == NULL) { // if node is empty, return null
        return NULL;
    }

    if (l->item == x) { // if item is found, return that node
        return l;
    }

    if (x < l->item) { // if value to be found is less than current node's value, search the left node
        return search_tree(l->left, x);
    }
    else {
        return search_tree(l->right, x); // else, search the right node
    }
}


// FINDING MINIMUM AND MAXIMUM
// minimum will be the bottom left node
// maximum will be the bottom right node
// o complexity is O(log n) or O(height of tree). each recursion step moves one level down the tree, splitting in half
tree* find_minimum(tree* t) { // finding minimum
    tree* min; // make a node to hold current node, starting from root
    if (t == NULL) {
        return NULL; // if empty, return null
    }

    min = t; // set current node
    while (min->left != NULL) { // while there are still nodes to the left
        min = min->left; // set current node as left child
    }
    return min;
}


// TRAVERSAL means visiting all nodes in the tree
// many methods of traversal, including 
// in-order (from bottom left to upper middle to bottom right)
// pre-order (from root node to left subtree to right subtree)
// post-order (from left subtree to right subtree to root node)
// level order (traverse all nodes in current level from left to right, then move down to next level)
// can obtain each method by changing where the processing position is. pre-order is processing first, post-order is processing last

// each recursive call pauses the execution of the current function and moves deeper into the left or right subtree. 
// When a recursive call finishes, control "returns" to the parent function where it left off. This is how the program "backtracks" to the parent node.

// example of inorder traversal
// o complexity of O(n) since each item is processed once during traversal, n = num of nodes
void traverse_tree(tree* l) {
    if (l != NULL) {
        traverse_tree(l->left);
        cout << l->item << " "; // processing the item
        traverse_tree(l->right);
    }
}


// INSERTION
// o complexity of O(log n) or O(height of tree) because it is searching for position
void insert_tree(tree** l, int x, tree* parent) {
    tree* newNode;

    if (*l == NULL) { // if a valid empty spot is available after recursively finding correct position
        newNode = new tree(); // insert the node
        newNode->item = x;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = parent;
        *l = newNode; // sets the parent of the inserted node to point to the new node. at this point, l represents the parent node (look at parameters of function and in the recursion)
        return;
    }

    if (x < (*l)->item) { // if value is less than current item
        insert_tree(&((*l)->left), x, *l); // move to the left child
    }
    else {
        insert_tree(&((*l)->right), x, *l); // move to the right child
    }
}
