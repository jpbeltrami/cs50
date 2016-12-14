#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool validarg(string a);

int main(int argc, string argv[])
{   
    //checks there is 1 word for the key
    if(argc != 2)
    {
        printf("Enter 1 word for the key!\n");
        return 1;
    }
    
    //checks there are only letters in key
    if(!validarg(argv[1]))
    {
        printf("Only letters for the key!\n");
        return 1;
    }
    
    //stores keyword in string k
    string k = argv[1];
    
    //takes plain text from user
    string p = GetString();
    
    int c;
    int e;
    int q;
    int j = 0;
    int l = strlen(k);
    
    //encrypts plaintext using keyword
    for(int i = 0, n = strlen(p); i < n; i++)
    {
        //makes alphabetical index of key
        if((isalpha(p[i])))
        {
            q = j % l;
            
            if(islower(k[q]))
            {
                e = (k[q] - 97);
            }
            
            if(isupper(k[q]))
            {
                e = (k[q] - 65);
            }
            
            j++;
        }
        
        else
        {
            printf("%c", p[i]);
            continue;
        }
        
        //encrypts
        if(islower(p[i]))
        {
            c = ((p[i] - 97) + e) % 26;
            printf("%c", 97 + c);
            continue;
        }
            
        else if(isupper(p[i]))
        {
            c = ((p[i] - 65) + e) % 26;
            printf("%c", 65 + c);
            continue;
        }
    }

    printf("\n");
    
    return 0;
}

bool validarg(string a)
{
    for(int i = 0, n = strlen(a); i < n; i++)
    {
        if(!(isalpha(a[i])))
        {
            return false;
        }
    }
    
    return true;
}