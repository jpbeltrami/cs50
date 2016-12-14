/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>


#include "dictionary.h"

// the alphabet includes an apostrophe
#define ALPHABETNUM 27
#define NEWLINE 10
#define APOSTROPHE 39

typedef struct node
{
    bool is_word;
    struct node* children[ALPHABETNUM];
} node;

node * root;
unsigned int wrd_count = 0;
bool gload = false;

// this is a funtion finds the last node and erases it.
// it will return NULL if successful otherwise it returns the path.
void eraser (node * path)
    {
        for(int i = 0; i < ALPHABETNUM; i++)
        {
            // If there is a non-null node then enter it.
            if(path->children[i] != NULL)
            {
                eraser(path->children[i]);
                continue;
            }

            free(path->children[i]);
        }
        
        free(path);
        
    }

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int c = 0;
    node * checkr = NULL;
    bool new_word = true;
    int word_len = strlen(word);
    
    for(int i = 0; i < word_len; i++)
    {
        // is it the start of a new word?
        if (new_word == true)
        {
            checkr = root;
        }
        
        c = (int) word[i];
        
        if(c == 39)
        c = ALPHABETNUM - 1;
        
        else if(c != 10 || c != 39)
        c = tolower(c) - 'a';
        
        // if you reach NULL then it's not in the dictionary.
        if (checkr->children[c] == NULL)
        {
            new_word = true;
            break;
        }
        
        // if the node contains the letter.
        else if (checkr->children[c] != NULL)
        {
            new_word = false;
            checkr= checkr->children[c];
            
            // Is this the end of the word?
            if (checkr->is_word == true && (word_len - i == 1))
            {

                return true;
            }
        }
    }

    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = calloc(1, sizeof(node));
    if (root == NULL)
    {
        printf("Memory error\n");
        return false;
    }
    node * cursor = root;
    
    // Open the dictionary file.
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s file.\n", dictionary);
        fclose(fp);
    }
    
    // Go through each letter in dictionary file
    for(int c = (fgetc(fp)); c != EOF; c = fgetc(fp))
    {   
        // set c = right index number for the array
        if(c == APOSTROPHE)
        {
            c = ALPHABETNUM - 1;
        }
        
        else if (c == NEWLINE)
        {
            cursor->is_word = true;
            cursor = root;
            wrd_count++;
            continue;
        }
        
        else
        {
            c = tolower(c) - 'a';
        }
        
        
        if(cursor->children[c] == NULL)
        {
            cursor->children[c] = calloc(1, sizeof(node));
            if (cursor->children[c] == NULL)
            {
                printf("Memory error\n");
                return false;
            }
            cursor = cursor->children[c];
        }
        
        else if(cursor->children[c] != NULL)
        {
            cursor = cursor->children[c];
            continue;
        }
    }
    
    gload = true;
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // if successfully loaded return wrd_count else return 0;
    if (gload == true) 
        return wrd_count;
        
    else     
    return 1;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{  
    eraser(root);
    return true;
}