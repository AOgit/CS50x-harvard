#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);
void bricks_block(int bricks);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        print_row(height - i - 1, i + 1 );
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // Print bricks
    bricks_block(bricks);
    // Print bricks delimiter
    printf("  ");
    // Print again bricks
    bricks_block(bricks);
    printf("\n");
}

void bricks_block(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}
