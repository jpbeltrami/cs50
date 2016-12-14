#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int minutes;
    
    printf("minutes:");
    
    minutes = GetInt();

    printf("bottles:%d\n", minutes * 12);
}