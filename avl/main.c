#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    printf("=== DEMONSTRAÇÃO ÁRVORE AVL ===\n");
    printf("Inserindo sequência que desbalancearia uma BST comum: 1,2,3,4,5,6,7\n\n");

    AVLTree *tree = AVLTree_create();

    
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
    {
        AVLTree_insert(tree, values[i]);

        printf("Estado após inserir %d:\n", values[i]);
        printf("Inorder: ");
        AVLTree_inorder(tree->root);
        printf("\n");

        printf("É AVL válida? %s\n", isAVLUtil(tree->root) ? "SIM" : "NÃO");
        AVLTree_printByLevels(tree);
        printf("\n");
    }

    printf("\n=== TESTE DE REMOÇÃO ===\n");
    AVLTree_delete(tree, 4);
    printf("Após remover 4:\n");
    printf("Inorder: ");
    AVLTree_inorder(tree->root);
    printf("\n");
    AVLTree_printByLevels(tree);

    return 0;
}