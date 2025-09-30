// Scrabble game, judge whose words have higher score
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int cal_score(string word);
void judge(int s1, int s2);

// Scores corresponding to each letter
const int SCORES[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{

    // Get 2 players' input
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate each one's score
    int score1 = cal_score(word1);
    int score2 = cal_score(word2);

    // Compare score and show result
    judge(score1, score2);
}

// Calculate score by each letter
int cal_score(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
        {
            int j = toupper(word[i]) - 'A';
            score += SCORES[j];
        }
    }
    return score;
}

// Compare 2 score
void judge(int s1, int s2)
{
    if (s1 > s2)
    {
        printf("Player 1 wins!\n");
    }
    else if (s1 < s2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
