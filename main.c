#include <stdio.h>
#include "SearchBinTree.h"

void PrintTree(BinTree *T)
{
    BinTree_pre(T->root);
    putchar('\n');
    BinTree_in(T->root);
    putchar('\n');
    putchar('\n');
    if (BinTree_isBST(T))
        printf("É uma BST válida!\n");
    else
        printf("NÃO é uma BST!\n");
}

int main()
{
    char input[256];
    printf("Enter tree in format (value(left_subtree)(right_subtree)): ");
    fgets(input, sizeof(input), stdin);
    int pos = 0;
    BinTree *tree = BinTree_create_from_string(input);

    PrintTree(tree);

    return 0;
}