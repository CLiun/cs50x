#include <cs50.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    string strings[] = {"abandon", "battleship", "boot",
                        "camp", "divide", "error"};

    string s = get_string("Your words: ");
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found.\n");
            return 0;
        }
    }
    printf("Not found.\n");
    return 1;
}
