#include <stdio.h>
#include "SearchBinTree.h"

void PrintTree(BinTree *T)
{
    BinTree_pre(T->root);
    putchar('\n');
    BinTree_in(T->root);
    putchar('\n');
}
int main()
{
    int V[] = {10, 5, 2, 7, 20, 15, 25};
    BinTree *T = BinTree_create();
    for (int i = 0; i < 7; i++)
        if (!BinTree_insert(T, V[i]))
            printf("Erro ao inserir o elemento V[%i] = %i\n", i, V[i]);
    PrintTree(T);
    int key = 10;
    printf("Removendo o elemento %i\n", key);
    if (BinTree_delete(T, key))
        PrintTree(T);
    else
        printf("Erro ao remover o elemento %i\n", key);

    return 0;
}