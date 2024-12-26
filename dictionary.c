// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26*45 + 45;

// Hash table
node *table[N];

// Global var size of dictionary
unsigned int size_dict = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    unsigned int hsh;
    hsh = hash(word);

    node *curr = table[hsh];
    while(curr != NULL)
    {
        if (strcasecmp(curr->word, word) == 0)
            return true;
        curr = curr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{



    // hash summ of word`s chars and place (unick hash?)
 /*    int i = 0;
    int summ = 0;
    while (word[i] != '\0')
    {
        summ += word[i] !='\'' ?  (toupper(word[i]) - 'A') + i : 0;
        i++;
    }
    return summ;*/


    // hash summ of word`s chars
    int i = 0;
    int summ = 0;
    while (word[i] != '\0')
    {
        summ += word[i] !='\'' ?  toupper(word[i]) - 'A' : 0;
        i++;
    }
    return summ;

    // TODO: Improve this hash function
   //  return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error open dictionary: %s\n", dictionary);
        return false;
    }

    char c;
    int i = 0;
    unsigned int hsh;
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        return false;
    }

    while (fread(&c, 1, sizeof(char), file))
    {
        if (c != '\n')
        {
            new->word[i] = c;
            i++;
        }else
        {
            new->word[i] = '\0';
            // Returns true if word is in dictionary, else false
            hsh = hash(new->word);
            if (table[hsh] == NULL)
            {
                table[hsh] = new;
            } else {
                new->next = table[hsh]->next;
                table[hsh]->next = new;
            }

            new = malloc(sizeof(node));
            if (new == NULL)
            {
                return false;
            }
            size_dict++;
            i = 0;
        }

    }

    free(new);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_dict ? size_dict : 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
   node *new;

    for (int i = 0; i < N; i++)
    {
        new = table[i];
        while (new != NULL)
        {
            table[i] = new->next;
            free(new);
            new = table[i];
        }
    }
    free(new);
    return true;
}
