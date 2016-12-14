/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
typedef uint8_t BYTE;

typedef struct
{
    BYTE jpgu[512];
}BLOCK;

int main(void)
{
    // open file
    FILE* inptr = fopen("card.raw", "r");
    FILE* img = NULL;
    BLOCK data;
    char* title = malloc(sizeof("%0.3d.jpg") + 1);
    int ctr = 0;
    int openCheck = 0;
    
    // check it's ok
    if(inptr == NULL)
    {
        printf("Could not open card file\n");
        return 1;
    }
    
    // repeat until end of card
    while(fread(&data, sizeof(BLOCK), 1, inptr) == 1)
    {
        // start of a new jpg?
        
        if(data.jpgu[0] == 0xff && data.jpgu[1] == 0xd8 && data.jpgu[2] == 0xff &&
        (data.jpgu[3] == 0xe0 || data.jpgu[3] == 0xe1 || data.jpgu[3] == 0xe2 || 
        data.jpgu[3] == 0xe3 || data.jpgu[3] == 0xe4 || data.jpgu[3] == 0xe5 || 
        data.jpgu[3] == 0xe6 || data.jpgu[3] == 0xe7 || data.jpgu[3] == 0xe8 || 
        data.jpgu[3] == 0xe9 || data.jpgu[3] == 0xea || data.jpgu[3] == 0xeb || 
        data.jpgu[3] == 0xec || data.jpgu[3] == 0xed || data.jpgu[3] == 0xee || 
        data.jpgu[3] == 0xef))
        {
            if(ctr != 0)
            {
                fclose(img);
            }
            
            // open new jp
            
            sprintf(title, "%0.3d.jpg", ctr);
            img = fopen(title, "w");
            
            if(img == NULL)
            {
                printf("Could not create %s", title);
                return 2;
            }
            
            ctr++;
            openCheck = 1;
        }
        // already found a new jpg?
        // no
        else if(openCheck == 0)
        {
            continue;
        }
        
        // yes
        if(openCheck != 0)
        {
            fwrite(&data, sizeof(BLOCK), 1, img);
        }
    }
    free(title);
    fclose(img);
    fclose(inptr);
    
    return 0;
}
