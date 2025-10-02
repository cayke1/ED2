#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    int *data;    // array que armazena os elementos
    int size;     // quantidade de elementos atualmente no heap
    int capacity; // capacidade máxima do heap
} Heap;

// Cria um heap com capacidade definida
Heap *Heap_create(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (int *)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Troca dois elementos
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Max_Heapify(Heap *heap, int i)
{
    int e = 2 * i;     // filho esquerdo
    int d = 2 * i + 1; // filho direito

    int maior = i;

    if (e < heap->size && heap->data[e] > heap->data[i])
    {
        maior = e;
    }

    if (d < heap->size && heap->data[d] > heap->data[maior])
    {
        maior = d;
    }

    if (maior != i)
    {
        swap(&heap->data[i], &heap->data[maior]);
        Max_Heapify(heap, maior);
    }
}

void HeapSort(Heap *heap)
{
    for (int i = heap->size - 1; i > 0; i--)
    {
        swap(&heap->data[0], &heap->data[i]);
        heap->size--;
        Max_Heapify(heap, 0);
    }
}
// Insere no max-heap
bool Heap_insert(Heap *heap, int value)
{
    if (heap->size >= heap->capacity)
        return false;

    int i = heap->size;
    heap->data[i] = value;
    heap->size++;

    // "Sobe" o elemento até a posição correta
    while (i != 0 && heap->data[(i - 1) / 2] < heap->data[i])
    {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return true;
}

void Build_Max_Heap(Heap *heap)
{
    for (int i = (heap->size / 2) - 1; i >= 0; i--)
    {
        Max_Heapify(heap, i);
    }
}

// Extrai o maior elemento (raiz)
int Heap_extract_max(Heap *heap)
{
    if (heap->size <= 0)
        return -1; // heap vazio
    if (heap->size == 1)
    {
        heap->size--;
        return heap->data[0];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    Max_Heapify(heap, 0);

    return root;
}

// Imprime em níveis (BFS)
void Heap_print(Heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        return;
    }

    int level = 0;
    int count = 0;
    int elems_in_level = 1;

    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->data[i]);
        count++;

        if (count == elems_in_level)
        {
            printf("\n");
            level++;
            elems_in_level = 1 << level; // 2^level
            count = 0;
        }
    }
    printf("\n");
}

// Liberar memória
void Heap_free(Heap *heap)
{
    free(heap->data);
    free(heap);
}
