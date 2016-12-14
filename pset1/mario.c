#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    
    do
    {
        printf("height: ");
        
        h = GetInt();
    }
    while(h > 23 || h < 0);
    
    for(int i = 0; i < h; i++)
    {
        for(int spc = 0; spc < (h - (i + 1)); spc++)
        {
            printf(" ");
        }
        
        for(int hsh = 0; hsh < (i + 2); hsh++)
        {
            printf("#");
        }
        printf("\n");
    }
}