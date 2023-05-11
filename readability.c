#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Get text from the user
    string text = get_string("Text: ");

    // Get text length
    int len = strlen(text);

    // Initiate variables
    int letters = 0;
    int words = 1;
    int sentences = 0;
    float score = 0.0;
    int grade_lvl = 0;
    float L = 0.0;
    float S = 0.0;

    // Count number of letters
    for (int i = 0; i < len; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'z')
        {
            letters++;
        }
    }

    //Count number of words
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }

    //Count number of sentences
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    //Find L and S
    L = letters * 100.0 / words;
    S = sentences * 100.0 / words;

    //DEBUG: check L and S values
    // printf("L: %.3f\n", L);
    // printf("S: %.3f\n", S);

    // Feed info into equation
    score = (0.0588 * L) - (0.296 * S) - 15.8;

    // DEBUG: check actual score
    // printf("Score: %.2f\n", score);

    grade_lvl = round(score);

    // Print reading level
    if (score >= 1 && score < 16)
    {
        printf("Grade %i\n", grade_lvl);
    }
    else if (score >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

    // DEBUG: check letters, words, sentences counts
    // printf("Letters: %i\n", letters);
    // printf("Words: %i\n", words);
    // printf("Sentences: %i\n", sentences);
}