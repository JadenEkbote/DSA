#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;
// Function to create a new Trie node
TrieNode *getNode(void)
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Function to insert a word into the Trie
void insert(TrieNode *root, const char *key)
{
    TrieNode *crawler = root;
    while (*key)
    {
        int index = *key - 'a';
        if (!crawler->children[index])
        {
            crawler->children[index] = getNode();
        }
        crawler = crawler->children[index];
        key++;
    }
    crawler->isEndOfWord = true;
}

// Function to search for a word in the Trie
bool search(TrieNode *root, const char *key)
{
    TrieNode *crawler = root;
    while (*key)
    {
        int index = *key - 'a';
        if (!crawler->children[index])
        {
            return false;
        }
        crawler = crawler->children[index];
        key++;
    }
    return (crawler != NULL && crawler->isEndOfWord);
}

// Function to check if a node has any children
bool hasNoChildren(TrieNode *node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i])
        {
            return false;
        }
    }
    return true;
}

// Function to delete a word from the Trie
bool delete(TrieNode *root, const char *key, int depth)
{
    // If the tree is empty
    if (!root)
    {
        return false;
    }

    // If last character of key is being processed
    if (*key)
    {
        int index = *key - 'a';
        if (delete (root->children[index], key + 1, depth + 1))
        {
            // Last character, so delete it
            free(root->children[index]);
            root->children[index] = NULL;

            // Return true if root has no children
            return (!root->isEndOfWord && hasNoChildren(root));
        }
    }

    // If not the last character
    else
    {
        // This node is no more end of word
        if (root->isEndOfWord)
        {
            root->isEndOfWord = false;

            // If root has no children, delete it
            return hasNoChildren(root);
        }
    }

    return false;
}

// Driver
int main()
{
    // Sample keys to be inserted in the Trie
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};

    // Root Trie node
    TrieNode *root = getNode();

    // Construct Trie
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        insert(root, keys[i]);
    }

    // Search for different keys
    printf("%s --- %s\n", "the", search(root, "the") ? "Found" : "Not Found");
    printf("%s --- %s\n", "these", search(root, "these") ? "Found" : "Not Found");
    printf("%s --- %s\n", "their", search(root, "their") ? "Found" : "Not Found");
    printf("%s --- %s\n", "thaw", search(root, "thaw") ? "Found" : "Not Found");

    // Deleting a word
    delete (root, "the", 0);

    // Searching after deletion
    printf("%s --- %s\n", "the", search(root, "the") ? "Found" : "Not Found");

    return 0;
}
