// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 + 26 * 26;

// Hash table
node *table[N] = {NULL};

// Count size of dictionary
unsigned int cnt = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Calculate hash value for word
    unsigned int index = hash(word);
    // Search the corresponding linked list for word
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    // End of list, not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int first_letter = toupper(word[0]) - 'A';
    if (strlen(word) == 1)
    {
        return first_letter;
    }
    int second_letter = toupper(word[1]) - 'A';
    return (first_letter + 1) * 26 + second_letter;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dict file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    // Read word of the dict, use fscanf(file, "%s", word)
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    // Add key into hash table
    {
        unsigned int hash_value = hash(word);
        // Allocate new node for word, return if no memory
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word);
        // Insert into linked list
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        cnt++;
    }
    // Close dict file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return cnt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
            cnt--;
        }
    }
    return true;
}
