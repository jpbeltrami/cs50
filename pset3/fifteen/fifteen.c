/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
int init(int a);
void draw(int string[DIM_MAX][DIM_MAX], int a);
bool move(int tile);
bool won(int string[DIM_MAX][DIM_MAX], int a);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(board, d);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(board, d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
int init(int a)
{
    int tileVal = (d * d);
    int temp;

    if(d % 2 == 0)
    {
     for( int i = 0 ; i < d ; i++)
    {
        for( int j = 0 ; j < d; j++)
        {
            tileVal--;
            board[i][j] = tileVal;
        }
    }
        temp = board[(d - 1)][(d - 2)];
        board[(d - 1)][(d - 2)] = board[(d - 1)][(d - 3)];
        board[(d - 1)][(d - 3)] = temp;
    }
    
    else
    {
    for( int i = 0 ; i < d ; i++)
    {
        for( int j = 0 ; j < d; j++)
        {
            tileVal--;
            board[i][j] = tileVal;
        }
    }

    }

    return board[d][d];
}
/**
 * Prints the board in its current state.
 */
void draw(int string[DIM_MAX][DIM_MAX], int a)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(string[i][j] >= 1 && string[i][j] <= 9)
            {
                printf("   %d", string[i][j]);
                continue;
            }
            if(string[i][j] == 0)
            {
                printf("   _");
            }
            else
            printf("  %d", string[i][j]);
        }
        
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int temp;
    int hor;
    int vert;
    
    //Go through each tile and find the position in the board of the tile.
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                hor = i;
                vert = j;
                break;
            }
        }
    }
    
    //check if the tile next to the tile entered by the player 
    //is next to the empty space and switch
    
    if (board[hor + 1][vert] == 0 && (hor + 1) < d)
    {
        //Do the switch
        temp = board[hor][vert];
        board[hor][vert] = board[hor + 1][vert];
        board[hor + 1][vert] = temp;
        
        return true;
    }
    
        if (board[hor - 1][vert] == 0 && (hor - 1) >= 0)
    {
        //Do the switch
        temp = board[hor][vert];
        board[hor][vert] = board[hor - 1][vert];
        board[hor - 1][vert] = temp;
        
        return true;
    }
    
        if (board[hor][vert + 1] == 0 && (vert + 1) < d)
    {
        //Do the switch
        temp = board[hor][vert];
        board[hor][vert] = board[hor][vert + 1];
        board[hor][vert + 1] = temp;
        
        return true;
    }
    
        if (board[hor][vert - 1] == 0 && (vert - 1) >= 0)
    {
        //Do the switch
        temp = board[hor][vert];
        board[hor][vert] = board[hor][vert - 1];
        board[hor][vert - 1] = temp;
        
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int string[DIM_MAX][DIM_MAX], int a)
{
    int num = 1;
    int sol[DIM_MAX][DIM_MAX];
    int counter = 0;
    
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < a; j++)
        {
            sol[i][j] = num;
            
            if(i == (a - 1) && j == (a - 1))
            {
                if(sol[a - 1][a - 1] != (a * a))
                {
                    counter++;
                }
                
                continue;
            }
            
            if(sol[i][j] != string[i][j])
            {
                counter++;
            }
            
            num++;
        }
    }
    
    if(counter == 0)
    {
        return true;
    }

    return false;
}