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

/*
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
*/
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
        } else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            // Si las claves son iguales, no se permite la inserción.
            free(new_node->pair);
            free(new_node);
            return;
        }
    }

    new_node->parent = parent;

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    tree->current= new_node;
} 


TreeNode * minimum(TreeNode * x){
while (x->left != NULL) {
        x = x->left;
    }
    return x; 
}

/*
void removeNode(TreeMap * tree, TreeNode* node) {

}*/
void transplant(TreeMap * tree, TreeNode * u, TreeNode * v) {
    if (u == NULL || tree == NULL) return;

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
void removeNode(TreeMap * tree, TreeNode* node) {
    if (tree == NULL || node == NULL) return;

    if (node->left == NULL) {
        transplant(tree, node, node->right);
    } else if (node->right == NULL) {
        transplant(tree, node, node->left);
    } else {
        TreeNode * successor = minimum(node->right);
        if (successor->parent != node) {
            transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }
    free(node->pair);
    free(node);
} 
void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode * current = tree->root;
    while (current != NULL) {
        if (is_equal(tree, key, current->pair->key)) {
            tree->current = current;
            return current->pair;
        } else if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
    //return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    TreeNode * current = tree->root;
    Pair * result = NULL;
    while (current != NULL) {
        if (!tree->lower_than(current->pair->key, key)) {
            result = current->pair;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode * current = tree->root;
    if (current == NULL) return NULL;
    while (current->left != NULL) {
        current = current->left;
    }
    tree->current = current;
    return current->pair;
    //return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
