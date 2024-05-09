#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    //new->lower_than = lower_than;
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
    //return NULL;
}


/*void insertTreeMap(TreeMap * tree, void* key, void * value) {
TreeNode * new_node = createTreeNode(key, value);
    if (tree == NULL || new_node == NULL) return;

    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }

    TreeNode * current = tree->root;
    TreeNode * parent = NULL;

    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_node->parent = parent;

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}*/

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * new_node = createTreeNode(key, value);
    if (tree == NULL || new_node == NULL) return;

    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }

    TreeNode * current = tree->root;
    TreeNode * parent = NULL;

    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_node->parent = parent;

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

TreeNode * minimum(TreeNode * x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

void transplant(TreeMap * tree, TreeNode * u, TreeNode * v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

/*TreeNode * minimum(TreeNode * x){

    return NULL;
}*/


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
