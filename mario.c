#include <cs50.h>
#include <stdio.h>

void space(int q);
void block(int q);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height<1 || height>8);

    int i;
    for (i=0;i<height;i++)
    {
        space(height-i);
        block(i);
        printf("  ");
        block(i);
        printf("\n");
    }
}

void space(int q)
{
    int i;
    for (i=0;i<q-1;i++)
    {
        printf(" ");
    }
}

void block(int q)
{
    int i;
    for (i=0;i<=q;i++)
    {
        printf("#");
    }
}
