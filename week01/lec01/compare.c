#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int a = get_int("First number: ");
    int b = get_int("Second number: ");

    if (a > b)
    {
        printf("a is bigger than b.\n");
    }
    else if (a < b)
    {
        printf("a is smaller than b.\n");
    }
    else
    {
        printf("a is equal to b.\n");
    }

    return 0;
}
