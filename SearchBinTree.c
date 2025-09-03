#include "SearchBinTree.h"
#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <limits.h> // para INT_MIN e INT_MAX

bool isBSTUtil(TNo* node, int min, int max) {
    if (node == NULL)
        return true;

    if (node->key <= min || node->key >= max)
        return false;

    return isBSTUtil(node->left, min, node->key) &&
           isBSTUtil(node->right, node->key, max);
}

bool BinTree_isBST(BinTree* tree) {
    return isBSTUtil(tree->root, INT_MIN, INT_MAX);
}

TNo* TNo_createNFill(int key){
    TNo* novo = malloc(sizeof(TNo));
    if(novo){
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
    }
    return novo;
}
BinTree* BinTree_create(){
    BinTree* nova = malloc(sizeof(BinTree));
    if(nova)
        nova->root = NULL; //Estado da árvore vazia
    return nova;
}

bool BinTree_insert(BinTree* T, int key){
    TNo* z = TNo_createNFill(key);
    if(z == NULL)
        return false;
    TNo* y = NULL;
    TNo* x = T->root;
    while(x!=NULL){
        y = x;
        x = (z->key < x->key)? x->left:x->right;
    }
    z-> p = y;
    if (y==NULL)
        T->root = z;
    else
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    return true;
}
TNo* BinTree_search(TNo*, int);
void BinTree_pre(TNo* root){
    if(root){
        printf("%d, ", root->key);
        if(root->left)
            BinTree_pre(root->left);
        if(root->right)
            BinTree_pre(root->right);
    }
}
void BinTree_in(TNo* root){
    if(root){
        if(root->left)
            BinTree_in(root->left);
        printf("%d, ", root->key);
        if(root->right)
            BinTree_in(root->right);
    }

}
void BinTree_pos(TNo* root){
    if(root){
        if(root->left)
            BinTree_pos(root->left);
        if(root->right)
            BinTree_pos(root->right);
        printf("%d, ", root->key);
    }    
}

TNo* parseTree(const char* str, int* pos, TNo* parent) {
    if (str[*pos] != '(') return NULL;
    (*pos)++;


    if (str[*pos] == ')') {
        (*pos)++;
        return NULL;
    }


    int num = 0, sign = 1;
    if (str[*pos] == '-') {
        sign = -1;
        (*pos)++;
    }
    while (isdigit(str[*pos])) {
        num = num * 10 + (str[*pos] - '0');
        (*pos)++;
    }
    num *= sign;

    TNo* node = createNode(num);
    node->p = parent;

    node->left = parseTree(str, pos, node);


    node->right = parseTree(str, pos, node);

    (*pos)++;
    return node;
}

TNo* createNode(int key) {
    TNo* node = (TNo*) malloc(sizeof(TNo));
    node->key = key;
    node->left = node->right = node->p = NULL;
    return node;
}

BinTree* BinTree_create_from_string(const char* str) {
    BinTree* tree = (BinTree*) malloc(sizeof(BinTree));
    int pos = 0;
    tree->root = parseTree(str, &pos, NULL);
    return tree;
}