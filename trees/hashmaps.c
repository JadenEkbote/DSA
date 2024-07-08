#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Structure for each element in the hash map
struct node
{
    char *key;
    int value;
    struct node *next;
};

// Structure for the hash map itself
struct hashmap
{
    struct node *table[TABLE_SIZE];
};

// Hash function to calculate index
int hash_function(const char *key)
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

// Function to create a new node
struct node *create_node(const char *key, int value)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key); // Store a copy of the key
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Function to insert key-value pair into hash map
void hashmap_insert(struct hashmap *map, const char *key, int value)
{
    int index = hash_function(key);
    struct node *new_node = create_node(key, value);

    // Insert at the beginning of the linked list
    new_node->next = map->table[index];
    map->table[index] = new_node;
}

// Function to retrieve value associated with a key
int hashmap_get(struct hashmap *map, const char *key)
{
    int index = hash_function(key);
    struct node *current = map->table[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Key not found
}

// Function to delete a key-value pair from hash map
void hashmap_delete(struct hashmap *map, const char *key)
{
    int index = hash_function(key);
    struct node *current = map->table[index];
    struct node *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                map->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to free all memory used by hash map
void hashmap_destroy(struct hashmap *map)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct node *current = map->table[i];
        while (current != NULL)
        {
            struct node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        map->table[i] = NULL;
    }
}

// Example usage
int main()
{
    struct hashmap map;
    memset(&map, 0, sizeof(map)); // Initialize hash map

    // Inserting key-value pairs
    hashmap_insert(&map, "apple", 5);
    hashmap_insert(&map, "banana", 10);
    hashmap_insert(&map, "orange", 15);

    // Retrieving values
    printf("Value of 'apple': %d\n", hashmap_get(&map, "apple"));
    printf("Value of 'banana': %d\n", hashmap_get(&map, "banana"));
    printf("Value of 'orange': %d\n", hashmap_get(&map, "orange"));

    // Deleting a key-value pair
    hashmap_delete(&map, "banana");

    // Retrieving values after deletion
    printf("Value of 'banana' after deletion: %d\n", hashmap_get(&map, "banana"));

    // Destroying hash map
    hashmap_destroy(&map);

    return 0;
}
