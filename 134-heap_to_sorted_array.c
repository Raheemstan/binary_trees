#include <stdlib.h>
#include "binary_trees.h"

void heapifyDown(heap_t *node);

/**
 * heap_to_sorted_array - Converts a Binary Max Heap to a sorted array of integers
 * @heap: Pointer to the root node of the heap to convert
 * @size: Address to store the size of the array
 *
 * Return: Pointer to the sorted array of integers
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
    if (heap == NULL || size == NULL)
        return NULL;

    int count = 0;
    int *sorted_arr = malloc(sizeof(int) * *size);

    if (sorted_arr == NULL)
        return NULL;

    while (heap != NULL)
    {
        sorted_arr[count++] = heap->n;
        heapifyDown(heap);
    }

    for (int i = 0; i < count / 2; i++)
    {
        int temp = sorted_arr[i];
        sorted_arr[i] = sorted_arr[count - i - 1];
        sorted_arr[count - i - 1] = temp;
    }

    *size = count;
    return sorted_arr;
}

void heapifyDown(heap_t *node)
{
    heap_t *largest = node;
    heap_t *left = node->left;
    heap_t *right = node->right;

    if (left != NULL && left->n > largest->n)
        largest = left;

    if (right != NULL && right->n > largest->n)
        largest = right;

    if (largest != node)
    {
        int temp = node->n;
        node->n = largest->n;
        largest->n = temp;
        heapifyDown(largest);
    }
}
