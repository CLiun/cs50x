// Using command-line argument to encrypt message, by caesar algo
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_num(string argv);
char rotate(char ptext, int key);

int main(int argc, string argv[])
{
    // Check only 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check every character in argument is number
    else
    {
        if (!(only_num(argv[1])))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Convert string to int, guaranteed by input, < 2^31 - 26
    int key = atoi(argv[1]);
    // Get input plaintext
    string text = get_string("plaintext:  ");
    // Rotate if is letter
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        text[i] = rotate(text[i], key);
    }
    // Show ciphertext
    printf("ciphertext: %s\n", text);
    return 0;
}

// True only if all character is digit
bool only_num(string argv)
{
    for (int i = 0, len = strlen(argv); i < len; i++)
    {
        if (!isdigit(argv[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char ptext, int key)
{
    char ctext;
    if (islower(ptext))
    {
        int distance = (int) ptext - (int) 'a' + key;
        int offset = distance % 26;
        ctext = 'a' + offset;
    }
    else if (isupper(ptext))
    {
        int distance = (int) ptext - (int) 'A' + key;
        int offset = distance % 26;
        ctext = 'A' + offset;
    }
    else
    {
        ctext = ptext;
    }
    return ctext;
}
