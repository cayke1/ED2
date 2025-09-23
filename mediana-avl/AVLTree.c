#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

AVLTree *AVLTree_create()
{
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

TNo *createNode(int key)
{
    TNo *node = (TNo *)malloc(sizeof(TNo));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->p = NULL;
    node->height = 1;
    return node;
}

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
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

TNo *rightRotate(TNo *y)
{
    TNo *x = y->left;
    TNo *T2 = x->right;

    x->right = y;
    y->left = T2;

    x->p = y->p;
    y->p = x;
    if (T2 != NULL)
        T2->p = y;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TNo *leftRotate(TNo *x)
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

TNo *insertNode(TNo *node, int key, TNo *parent)
{
    if (node == NULL)
    {
        TNo *newNode = createNode(key);
        newNode->p = parent;
        return newNode;
    }

    if (key < node->key)
    {
        node->left = insertNode(node->left, key, node);
    }
    else if (key > node->key)
    {
        node->right = insertNode(node->right, key, node);
    }
    else
    {
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
    {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key)
    {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool AVLTree_insert(AVLTree *tree, int key)
{
    if (tree == NULL)
        return false;
    tree->root = insertNode(tree->root, key, NULL);
    return true;
}

TNo *AVLTree_search(TNo *root, int key)
{
    if (root == NULL || root->key == key)
    {
        return root;
    }

    if (key < root->key)
    {
        return AVLTree_search(root->left, key);
    }

    return AVLTree_search(root->right, key);
}

void AVLTree_inorder(TNo *root)
{
    if (root != NULL)
    {
        AVLTree_inorder(root->left);
        printf("%d ", root->key);
        AVLTree_inorder(root->right);
    }
}

void AVLTree_preorder(TNo *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        AVLTree_preorder(root->left);
        AVLTree_preorder(root->right);
    }
}

void AVLTree_postorder(TNo *root)
{
    if (root != NULL)
    {
        AVLTree_postorder(root->left);
        AVLTree_postorder(root->right);
        printf("%d ", root->key);
    }
}

bool isAVLUtil(TNo *root)
{
    if (root == NULL)
        return true;

    int balance = getBalance(root);

    if (balance > 1 || balance < -1)
        return false;

    return isAVLUtil(root->left) && isAVLUtil(root->right);
}

TNo *buildBSTFromMedian(int arr[], int start, int end, TNo *parent)
{
    if (start > end)
        return NULL;

    int mid = start + (end - start) / 2;
    TNo *node = createNode(arr[mid]);
    node->p = parent;

    node->left = buildBSTFromMedian(arr, start, mid - 1, node);
    node->right = buildBSTFromMedian(arr, mid + 1, end, node);

    return node;
}

bool treesEqual(TNo *tree1, TNo *tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return true;

    if (tree1 == NULL || tree2 == NULL)
        return false;

    if (tree1->key != tree2->key)
        return false;

    return treesEqual(tree1->left, tree2->left) &&
           treesEqual(tree1->right, tree2->right);
}

void freeTree(TNo *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
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
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool AVLTree_delete(AVLTree *tree, int key)
{
    printf("\n=== Removendo %d ===\n", key);
    tree->root = AVL_deleteNode(tree->root, key);
    return true;
}