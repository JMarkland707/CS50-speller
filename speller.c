// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table, creates linked list, table will reach into node for data
node *table[N];


// Declared Variables
unsigned int word_count;
unsigned int hash_value;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word and obtain hash value
    hash_value = hash(word);

    // Point cursor to the first node
    // Pointer is our variable that we are telling to grab data from this location
    node *cursor = table[hash_value];

    // Go through the linked list
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0) // Compare the word w/ Cursor and if they match return true
        {
            return true;
        }
        // If it does not match, move cursor to the next word
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    // Read each word in the file and add to hash table, fscanf() and EOF
    char buffer[LENGTH + 1];
    while (fscanf(source, "%s", buffer) != EOF)
    {

       node *n = malloc(sizeof(node));
       if (n == NULL)
       {
        return false;
       }
    // Copy the string of buffer into word field of node
       strcpy(n->word, buffer);
       hash_value = hash(buffer);
       n->next = table[hash_value];
       table[hash_value] = n;
       word_count++;
    }
    // Close the file
    fclose(source);
    // If everything works
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Go through buckets in hash table
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the linked list
        node *cursor = table[i];

        // If cursor is not NULL, free memory
        while (cursor != NULL)
        {
            // Create tmp
            node *tmp = cursor;
            //Move cursor to next node
            cursor = cursor->next;
            // Free Temp
            free(tmp);
        }
    }
    return true;
}

