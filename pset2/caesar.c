#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    //check that one key is entered
    if(argc !=2)
    {
        printf("Enter ONE number please\n");
        
        return 1;
    }
    
    //converts key to int
    int k = atoi(argv[1]);
    int c = 0;
    //Gets plaintext from user
    string p = GetString();
    
    //converts and outputs cyphertext
    for(int i = 0, n = strlen(p); i < n; i++)
    {
        if(isalpha(p[i]))
        {
            if(islower(p[i]))
            {
                c = ((p[i] - 97) + k) % 26;
                printf("%c", 97 + c);
                continue;
            }
            
            else if(isupper(p[i]))
            {
                c = ((p[i] - 65) + k) % 26;
                printf("%c", 65 + c);
                continue;
            }
        }
        else
        printf("%c", p[i]);
    }
    
    printf("\n");
    
    return 0;
}