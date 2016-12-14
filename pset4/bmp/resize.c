/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    // remember new size factor
    int n = atoi(argv[1]);
    
    // ensure n is positive and smaller than 100
    if (n <= 0 || n > 100)
    {
        printf("n must be positive and smaller than 100\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER origBf;
    fread(&origBf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER origBi;
    fread(&origBi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // declare outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf = origBf;
    
    // declare outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi = origBi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (origBf.bfType != 0x4d42 || origBf.bfOffBits != 54 || origBi.biSize != 40 || 
        origBi.biBitCount != 24 || origBi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // determine input image padding
    int origPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change width and height for output file
    bi.biHeight = (origBi.biHeight * n);
    bi.biWidth = (origBi.biWidth * n);

    // determine padding for scanlines
    int nuPadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change image size
    bi.biSizeImage = (((bi.biWidth * abs(bi.biHeight)) * 3) + (nuPadding * abs(bi.biHeight)));
    
    // change file size (including header files)
    bf.bfSize = bi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    int i;

    // read over infile's scanlines
    for (i = 0, origBi.biHeight = abs(origBi.biHeight); i < origBi.biHeight; i++)
    {
        // temporary storage
        RGBTRIPLE triple;
        RGBTRIPLE newLine[bi.biWidth];
        int lineCtr = 0;
        
        // horizontal write
        for(int j = 0; j < origBi.biWidth; j++)
        {
            // read pixel from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write pixel n - 1 times with new width and save to lineCtr 
            // the # of times it was written
            for(int k = 0; k < n; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                newLine[lineCtr] = triple;
                lineCtr++;
            }
        }
        
        // print padding into output file
        for (int p = 0; p < nuPadding; p++)
        {
            fputc(0x00, outptr);
        }
        
        // vertical rewrite
        for (int r = 0; r < (n - 1); r++)
        {
            // write pixels
            for (int q = 0; q < bi.biWidth; q++)
            {
                fwrite(&newLine[q], sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // write padding
            for (int p = 0; p < nuPadding; p++)
            {
                fputc(0x00, outptr);
            }
        }
        // skip over padding of input file, if any
        fseek(inptr, origPadding, SEEK_CUR);
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
