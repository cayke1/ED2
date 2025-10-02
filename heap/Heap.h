#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>
typedef struct
{
    int *data;
    int size;
    int capacity;
} Heap;
Heap *Heap_create(int capacity);
bool Heap_insert(Heap *heap, int value);
int Heap_extract_max(Heap *heap);
void Heap_free(Heap *heap);
void Heap_print(Heap *heap);
void Max_Heapify(Heap *heap, int i);
void HeapSort(Heap *heap);
#endif