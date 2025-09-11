#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getHeight(TNo *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(TNo *node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(TNo *node)
{
    if (node != NULL)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1+ (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

TNo *rotateRight(TNo *y)
{
    TNo *x = y->left;
    TNo *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    x->p = y->p;
    y->p = x;
    if (T2 != NULL)
        T2->p = y;
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

TNo *rotateLeft(TNo *x)
{
    TNo *y = x->right;
    TNo *T2 = y->left;

    y->left = x;
    x->right = T2;

    y->p = x->p;
    x->p = y;

    if (T2 != NULL)
        T2->p = x;

    updateHeight(x);
    updateHeight(y);

    return y;
}

TNo *TNo_createNFill(int key)
{
    TNo *novo = malloc(sizeof(TNo));
    if (novo)
    {
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
        novo->height = 1;
    }
    return novo;
}

AVLTree *AVLTree_create()
{
    AVLTree *nova = malloc(sizeof(AVLTree));
    if (nova)
        nova->root = NULL;
    return nova;
}

TNo *AVL_insertNode(TNo *node, int key)
{
    if (node == NULL)
        return TNo_createNFill(key);

    if (key < node->key)
    {
        node->left = AVL_insertNode(node->left, key);
        if (node->left != NULL)
            node->left->p = node;
    }

    else if (key > node->key)
    {
        node->right = AVL_insertNode(node->right, key);
        if (node->right != NULL)
            node->right->p = node;
    }
    else
    {
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    printf("Nó %d - Altura: %d, Balance: %d\n", node->key, node->height, balance);

    if (balance > 1 && key < node->left->key)
    {
        printf("Caso SE detectado no nó %d\n", node->key);
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key)
    {
        printf("Caso SD detectado no nó %d\n", node->key);
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->key)
    {
        printf("Caso DD detectado no nó %d\n", node->key);
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        printf("Caso DE detectado no nó %d\n", node->key);
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree_insert(AVLTree *tree, int key)
{
    printf("\n=== Inserindo %d ===\n", key);
    tree->root = AVL_insertNode(tree->root, key);
    return true;
}

TNo *findMin(TNo *node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

TNo *AVL_deleteNode(TNo *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
    {
        root->left = AVL_deleteNode(root->left, key);
    }

    else if (key > root->key)
    {
        root->right = AVL_deleteNode(root->right, key);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            TNo *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            TNo *temp = findMin(root->right);
            root->key = temp->key;
            root->right = AVL_deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance <-1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if(balance <-1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

bool AVLTree_delete(AVLTree* tree, int key) {
    printf("\n=== Removendo %d ===\n", key);
    tree->root = AVL_deleteNode(tree->root, key);
    return true;
}

TNo* AVLTree_search(TNo* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    
    if (key < root->key)
        return AVLTree_search(root->left, key);
    
    return AVLTree_search(root->right, key);
}

void AVLTree_inorder(TNo* root) {
    if (root != NULL) {
        AVLTree_inorder(root->left);
        printf("%d(h:%d,b:%d) ", root->key, root->height, getBalance(root));
        AVLTree_inorder(root->right);
    }
}

void AVLTree_preorder(TNo* root) {
    if (root != NULL) {
        printf("%d(h:%d,b:%d) ", root->key, root->height, getBalance(root));
        AVLTree_preorder(root->left);
        AVLTree_preorder(root->right);
    }
}

void AVLTree_postorder(TNo* root) {
    if (root != NULL) {
        AVLTree_postorder(root->left);
        AVLTree_postorder(root->right);
        printf("%d(h:%d,b:%d) ", root->key, root->height, getBalance(root));
    }
}

void printLevel(TNo *root, int level, int currentLevel)
{
    if (root == NULL)
    {
        if (currentLevel == level)
        {
            printf("NULL ");
        }
        return;
    }

    if (currentLevel == level)
    {
        printf("%d(h:%d) ", root->key, root->height);
        return;
    }

    printLevel(root->left, level, currentLevel + 1);
    printLevel(root->right, level, currentLevel + 1);
}

void AVLTree_printByLevels(AVLTree *tree)
{
    printf("\n=== Estrutura da Árvore AVL ===\n");
    int height = getHeight(tree->root);
    for (int i = 0; i < height; i++)
    {
        printf("Nível %d: ", i);
        printLevel(tree->root, i, 0);
        printf("\n");
    }
}

bool isAVLUtil(TNo *root)
{
    if (root == NULL)
        return true;

    int balance = getBalance(root);
    if (balance < -1 || balance > 1)
        return false;

    return isAVLUtil(root->left) && isAVLUtil(root->right);
}