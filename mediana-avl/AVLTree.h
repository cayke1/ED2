#ifndef AVL_TREE_H
#define AVL_TREE_H
#include<stdbool.h>

typedef struct _no{
    int key;                    
    struct _no *left;           
    struct _no *right;          
    struct _no *p;              
    int height;                 
}TNo;

typedef struct {
    TNo* root;                  
}AVLTree;

AVLTree* AVLTree_create();

bool AVLTree_insert(AVLTree *tree, int key);

bool AVLTree_delete(AVLTree* tree, int key);

TNo* AVLTree_search(TNo* root, int key);

void AVLTree_inorder(TNo* root);

void AVLTree_preorder(TNo* root);

void AVLTree_postorder(TNo* root);

void AVLTree_printByLevels(AVLTree *tree);

bool isAVLUtil(TNo *root);

TNo* createNode(int key);

int getHeight(TNo* node);

int getBalance(TNo* node);

void updateHeight(TNo* node);

TNo* rightRotate(TNo* y);

TNo* leftRotate(TNo* x);

TNo* insertNode(TNo* node, int key, TNo* parent);

void freeTree(TNo* root);

bool treesEqual(TNo* tree1, TNo* tree2);

TNo* buildBSTFromMedian(int arr[], int start, int end, TNo* parent);

#endif