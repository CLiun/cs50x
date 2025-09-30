#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("Input origin: ");
    char *t = malloc(strlen(s) + 1);
    int i = 0;
    while (s[i] != '\0')
    {
        t[i] = s[i];
        i++;
    }
    *(t + i) = '\0';
    t[0] = toupper(t[0]);
    printf("%s\n", t);
    printf("%s\n", s);
}
