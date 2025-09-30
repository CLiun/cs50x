// Get pyramid height, print
#include <cs50.h>
#include <stdio.h>

int get_height(void);
void show_pyramid(int height);
void show_block(int height, int i);
void show_space(int height, int i);

int main(void)
{
    // Get positive height, smaller than 24
    int height = get_height();
    // Print the pyramid
    show_pyramid(height);
}

// Get legal input as height of pyramid
int get_height(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height >= 24);
    return height;
}

// Show pyramid by row, like left side, gap, right side
void show_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Show space
        show_space(height, i);
        // Show block by #
        show_block(height, i);
        printf("  ");
        show_block(height, i);
        printf("\n");
    }
}

void show_space(int height, int i)
{
    for (int j = 0; j < height - i - 1; j++)
    {
        printf(" ");
    }
}

void show_block(int height, int i)
{
    for (int j = 0; j < i + 1; j++)
    {
        printf("#");
    }
}
