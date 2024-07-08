#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000 // Maximum size of the array

// Fenwick Tree structure
struct FenwickTree
{
    int size;
    int *tree;
};

// Function to initialize Fenwick Tree
struct FenwickTree *fenwick_tree_init(int size)
{
    struct FenwickTree *ft = (struct FenwickTree *)malloc(sizeof(struct FenwickTree));
    ft->size = size;
    ft->tree = (int *)calloc(size + 1, sizeof(int)); // Tree is 1-indexed, so size + 1

    return ft;
}

// Function to update Fenwick Tree
void fenwick_tree_update(struct FenwickTree *ft, int index, int delta)
{
    while (index <= ft->size)
    {
        ft->tree[index] += delta;
        index += index & -index; // Move to the next index with LSB set
    }
}

// Function to query prefix sum from 1 to index
int fenwick_tree_query(struct FenwickTree *ft, int index)
{
    int sum = 0;
    while (index > 0)
    {
        sum += ft->tree[index];
        index -= index & -index; // Move to the parent index
    }
    return sum;
}

// Function to free memory used by Fenwick Tree
void fenwick_tree_destroy(struct FenwickTree *ft)
{
    free(ft->tree);
    free(ft);
}

// Example usage
int main()
{
    int arr[] = {1, 3, 5, 2, 6, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct FenwickTree *ft = fenwick_tree_init(n);

    // Build Fenwick Tree
    for (int i = 1; i <= n; i++)
    {
        fenwick_tree_update(ft, i, arr[i - 1]);
    }

    // Query prefix sum
    int prefix_sum = fenwick_tree_query(ft, 4);
    printf("Prefix sum from index 1 to 4: %d\n", prefix_sum);

    // Update value at index 3
    fenwick_tree_update(ft, 3, 6 - arr[2]);
    arr[2] = 6; // Update original array

    // Query updated prefix sum
    prefix_sum = fenwick_tree_query(ft, 4);
    printf("Updated prefix sum from index 1 to 4: %d\n", prefix_sum);

    // Clean up
    fenwick_tree_destroy(ft);

    return 0;
}
