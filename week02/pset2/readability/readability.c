// Determine read level, based on the given text
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int cnt_letter(string text);
int cnt_word(string text);
int cnt_sent(string text);
int cal_level(int letters, int words, int sentences);
void show_level(int level);

int main(void)
{
    // Get text
    string text = get_string("Text: ");

    // Count letters, words, sentences in text
    int letters = cnt_letter(text);
    int words = cnt_word(text);
    int sentences = cnt_sent(text);
    // Compute Coleman-Liau index
    int level = cal_level(letters, words, sentences);
    // Show reading level
    show_level(level);
}

// Count every alphabeta
int cnt_letter(string text)
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Count as word, if previous char is not space, and current char is space
int cnt_word(string text)
{
    int words = 1;
    int pre_space = 0, cur_space = 0;
    // At least contain 1 word, so start from index 1
    for (int i = 1, len = strlen(text); i < len; i++)
    {
        cur_space = isspace(text[i]);
        if (!pre_space && cur_space)
        {
            words++;
        }
        pre_space = cur_space;
    }
    return words;
}

// Count when meeting . ! ?
int cnt_sent(string text)
{
    int sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
// Compute reading level, using formula given, return nearest integer
int cal_level(int letters, int words, int sentences)
{
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int level = round(index);
    return level;
}

// Show grade, based on level computed
void show_level(int level)
{
    if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (level < 16)
    {
        printf("Grade %i\n", level);
    }
    else
    {
        printf("Grade 16+\n");
    }
}
