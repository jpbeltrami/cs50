/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{   
    int min = 0;
    int max = (n - 1);
    
    while(n > 0)
    {  
        if(min >= max)
        {
            return false;
        }
        int midpoint = ((min + max)/2);
    
        if(values[midpoint] == value)
            return true;
        if(values[max] == value)
            return true;
        else if(values[min] == value)
            return true;
        
        if(values[midpoint] < value)
            {
                min = midpoint + 1;
                continue;
            }
            
        if(values[midpoint] > value)
            {
                max = midpoint - 1;
                continue;
            }
    }
    return false;
}

/**
 * Sorts array of n values.
*/
void sort(int values[], int n)
{
    int min;
    int pos;
    int counter = 0;
    
    for (int i = 0; i < (n - 1); i++)
        {
            min = values[i];
            
            for (int j = (i + 1); j < n; j++)
            {   
                if (values[j] < min)
                {
                   min = values[j];
                   pos = j;
                   counter++;
                }
            }
            
            if(counter != 0)
            {
            int temp = values[i];
            values[i] = min;
            values[pos] = temp;
            counter = 0;
            }
        }

}