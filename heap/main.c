#include "Heap.h"
#include <stdio.h>

int main() {
    Heap *heap = Heap_create(10);

    Heap_insert(heap, 40);
    Heap_insert(heap, 30);
    Heap_insert(heap, 20);
    Heap_insert(heap, 10);
    Heap_insert(heap, 25);

    printf("Heap inicial:\n");
    Heap_print(heap);

    
    printf("Extraindo: %d\n", Heap_extract_max(heap));
    printf("Heap depois do extract (max_heapify foi chamado):\n");
    Heap_print(heap);

    // Bagunçando manualmente (forçando erro)
    heap->data[0] = 5; // raiz muito menor
    printf("Heap bagunçado:\n");
    Heap_print(heap);

    
    Max_Heapify(heap, 0);
    printf("Heap corrigido com max_heapify:\n");
    Heap_print(heap);

    return 0;
}
