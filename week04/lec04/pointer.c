#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = "Hello!\n";
    printf("First letter: %c\n", *s);
    printf("Third letter: %c\n", *(s + 2));
    printf("Length: %lu\n", strlen(s));
}
