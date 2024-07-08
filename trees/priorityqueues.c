#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a min heap node
typedef struct
{
    int *arr;     // Array to hold the heap elements
    int capacity; // Maximum possible size of the min heap
    int size;     // Current number of elements in the min heap
} MinHeap;

// Function to create a min heap with given capacity
MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->arr = (int *)malloc(capacity * sizeof(int));
    return minHeap;
}

// Function to swap two elements in the heap
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to heapify a subtree with root at given index
void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->arr[left] < minHeap->arr[smallest])
        smallest = left;

    if (right < minHeap->size && minHeap->arr[right] < minHeap->arr[smallest])
        smallest = right;

    if (smallest != idx)
    {
        swap(&minHeap->arr[smallest], &minHeap->arr[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to insert a new key 'k' into the min heap
void insertMinHeap(MinHeap *minHeap, int k)
{
    if (minHeap->size == minHeap->capacity)
    {
        printf("Overflow: Could not insert key\n");
        return;
    }

    // First insert the new key at the end
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->arr[i] = k;

    // Fix the min heap property if it is violated
    while (i != 0 && minHeap->arr[i] < minHeap->arr[(i - 1) / 2])
    {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the minimum element from the min heap
int extractMin(MinHeap *minHeap)
{
    if (minHeap->size <= 0)
        return INT_MAX;

    if (minHeap->size == 1)
    {
        minHeap->size--;
        return minHeap->arr[0];
    }

    // Store the minimum value and remove it from the heap
    int root = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

// Function to get the minimum element from the min heap without removing it
int getMin(MinHeap *minHeap)
{
    return minHeap->arr[0];
}

// Function to delete a key stored at index i
void deleteKey(MinHeap *minHeap, int i)
{
    minHeap->arr[i] = INT_MIN;
    while (i != 0 && minHeap->arr[i] < minHeap->arr[(i - 1) / 2])
    {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    extractMin(minHeap);
}

// Driver program to test above functions
int main()
{
    MinHeap *minHeap = createMinHeap(11);
    insertMinHeap(minHeap, 3);
    insertMinHeap(minHeap, 2);
    deleteKey(minHeap, 1);
    insertMinHeap(minHeap, 15);
    insertMinHeap(minHeap, 5);
    insertMinHeap(minHeap, 4);
    insertMinHeap(minHeap, 45);

    printf("Extracted min value: %d\n", extractMin(minHeap));
    printf("Minimum value: %d\n", getMin(minHeap));

    return 0;
}
