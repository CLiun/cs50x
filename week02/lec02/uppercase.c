#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        printf("%c", toupper(name[i]));
    }
    printf("\n");
}
