// Encrypt text by substituion, based on key given as CL argument
// Key should be capital insensitive
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Array for checking repeated character
bool LETTER[26] = {false};

bool err_key(string key);
char substitute(char ptext, string key);
int main(int argc, string argv[])
{
    // Check number of arguments, prompt if invalid
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    // Check validity of key, prompt if invalid
    else
    {
        if (err_key(argv[1]))
        {
            return 1;
        }
    }
    // Get plaintext input
    string text = get_string("plaintext:  ");
    // Encrypt by substitution
    for (int i = 0, text_len = strlen(text); i < text_len; i++)
    {
        text[i] = substitute(text[i], argv[1]);
    }
    // Show ciphertext
    printf("ciphertext: %s\n", text);
    return 0;
}

// Check validity of key, prompt if invalid
bool err_key(string key)
{
    int len = strlen(key);
    // Check length of key
    if (len != 26)
    {
        printf("Key must have 26 characters.\n");
        return true;
    }
    // Chekc if key is alphabeta
    for (int i = 0; i < len; i++)
    {
        // Check repeated letter
        if (isalpha(key[i]))
        {
            key[i] = toupper(key[i]);
            int offset = key[i] - 'A';
            if (LETTER[offset] == false)
            {
                LETTER[offset] = true;
            }
            else
            {
                printf("Key must not have repeated characters.\n");
                return true;
            }
        }
        else
        {
            printf("Key must be alphabetical.\n");
            return true;
        }
    }
    // Good key, so return false
    return false;
}

// Implement of substitution
char substitute(char ptext, string key)
{
    char ctext;
    // Encrypt alphabeta
    if (isalpha(ptext))
    {
        // Text case preserved
        if (islower(ptext))
        {
            int text_offset = ptext - 'a';
            int key_offset = key[text_offset] - 'A';
            ctext = 'a' + key_offset;
        }
        else
        {
            int text_offset = ptext - 'A';
            int key_offset = key[text_offset] - 'A';
            ctext = 'A' + key_offset;
        }
    }
    // Non-alphabetical stay unchanged
    else
    {
        ctext = ptext;
    }
    return ctext;
}
