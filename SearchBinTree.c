#include "SearchBinTree.h"
#include <stdio.h>
#include <stdlib.h>
TNo *TNo_createNFill(int key)
{
    TNo *novo = malloc(sizeof(TNo));
    if (novo)
    {
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
    }
    return novo;
}
BinTree *BinTree_create()
{
    BinTree *nova = malloc(sizeof(BinTree));
    if (nova)
        nova->root = NULL; // Estado da árvore vazia
    return nova;
}

bool BinTree_insert(BinTree *T, int key)
{
    TNo *z = TNo_createNFill(key);
    if (z == NULL)
        return false;
    TNo *y = NULL;
    TNo *x = T->root;
    while (x != NULL)
    {
        y = x;
        x = (z->key < x->key) ? x->left : x->right;
    }
    z->p = y;
    if (y == NULL)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    return true;
}
TNo *BinTree_search(TNo *T, int key)
{
    TNo *root = T;
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return BinTree_search(root->left, key);
    else
        return BinTree_search(root->right, key);
}
void BinTree_pre(TNo *root)
{
    if (root)
    {
        printf("%d, ", root->key);
        if (root->left)
            BinTree_pre(root->left);
        if (root->right)
            BinTree_pre(root->right);
    }
}
void BinTree_in(TNo *root)
{
    if (root)
    {
        if (root->left)
            BinTree_in(root->left);
        printf("%d, ", root->key);
        if (root->right)
            BinTree_in(root->right);
    }
}
void BinTree_pos(TNo *root)
{
    if (root)
    {
        if (root->left)
            BinTree_pos(root->left);
        if (root->right)
            BinTree_pos(root->right);
        printf("%d, ", root->key);
    }
}

void BinTree_Transplant(BinTree *T, TNo *u, TNo *v)
{
    if (u->p == NULL)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v != NULL)
        v->p = u->p;
}

TNo *Tree_Minimum(TNo *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

bool BinTree_delete(BinTree *T, int key)
{
    TNo *z = BinTree_search(T->root, key);
    if (z == NULL)
        return false;
    if (z->left == NULL)
    {
        BinTree_Transplant(T, z, z->right);
    }
    else if (z->right == NULL)
    {
        BinTree_Transplant(T, z, z->left);
    }
    else
    {
        TNo *y = Tree_Minimum(z->right);
        if (y->p != z)
        {
            BinTree_Transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        BinTree_Transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
    free(z);
    return true;
}
