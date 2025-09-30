#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree? y/n ");
    if (c == 'y')
    {
        printf("You agreed.\n");
    }
    else if (c =='n')
    {
        printf("You disagreed.\n");
    }
    else
    {
        printf("Invalid answer.\n");
    }

    return 0;
}
