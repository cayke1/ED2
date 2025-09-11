#ifndef SEARCH_BIN_TREE_H
#define SEARCH_BIN_TREE_H
#include<stdbool.h>
typedef struct _no{
    int key;
    struct _no *left, *right, *p;
}TNo;

typedef struct {
    TNo* root;
}BinTree;

BinTree* BinTree_create();

bool BinTree_insert(BinTree*, int);
TNo* BinTree_search(TNo*, int);
void BinTree_pre(TNo*);
void BinTree_in(TNo*);
void BinTree_pos(TNo*);
TNo* createNode(int key);
BinTree* BinTree_create_from_string(const char* str);
bool BinTree_isBST(BinTree* tree);

#endif