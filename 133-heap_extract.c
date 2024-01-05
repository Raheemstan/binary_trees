#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int *arr;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Heap* heap, int idx) {
    int parent = (idx - 1) / 2;
    if (idx > 0 && heap->arr[parent] < heap->arr[idx]) {
        swap(&heap->arr[parent], &heap->arr[idx]);
        heapifyUp(heap, parent);
    }
}

void insert(Heap* heap, int value) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    heap->arr[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void heapifyDown(Heap* heap, int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int largest = idx;

    if (left < heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;

    if (right < heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;

    if (largest != idx) {
        swap(&heap->arr[idx], &heap->arr[largest]);
        heapifyDown(heap, largest);
    }
}

int extractMax(Heap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty. Cannot extract max element.\n");
        return -1;
    }

    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return max;
}

void deleteHeap(Heap* heap) {
    free(heap->arr);
    free(heap);
}

int main() {
    Heap* heap = createHeap(MAX_HEAP_SIZE);

    int array[] = {79, 47, 68, 87, 84, 91, 21, 32, 34, 2, 20, 22, 98, 1, 62, 95};
    int n = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < n; i++) {
        insert(heap, array[i]);
    }

    printf("Heap elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", extractMax(heap));
    }
    printf("\n");

    deleteHeap(heap);
    return 0;
}
