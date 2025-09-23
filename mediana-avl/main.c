#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVLTree.h"

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int removeDuplicates(int arr[], int n)
{
    if (n == 0)
        return 0;

    int j = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] != arr[j])
        {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

int main()
{
    int n;

    while (scanf("%d", &n) == 1)
    {
        int *values = (int *)malloc(n * sizeof(int));
        int *sortedValues = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &values[i]);
            sortedValues[i] = values[i];
        }

        bubbleSort(sortedValues, n);

        int uniqueSize = removeDuplicates(sortedValues, n);

        TNo *bstMedian = buildBSTFromMedian(sortedValues, 0, uniqueSize - 1, NULL);

        AVLTree *avlTree = AVLTree_create();
        for (int i = 0; i < n; i++)
        {
            AVLTree_insert(avlTree, values[i]);
        }

        int result = treesEqual(bstMedian, avlTree->root) ? 1 : 0;
        printf("%d\n", result);

        freeTree(bstMedian);
        freeTree(avlTree->root);
        free(avlTree);
        free(values);
        free(sortedValues);
    }

    return 0;
}