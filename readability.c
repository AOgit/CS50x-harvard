#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int coleman_index(string text);

int main(void)
{
    string text = get_string("Text: ");
   // string arr_word[0];

   // compute Coleman-Liau index
   int index = coleman_index(text);

   // show grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int coleman_index(string text)
{
    int words = 0;
    int sentences = 0;
    int letters = 0;

    //count letters, words, sentences
    for (int i=0, len = strlen(text); i < len; i++)
    {
       if (isalpha(text[i]))
       {
            letters++;
       }
       else if (text[i] == '.' || text[i] == '!' || text[i] == '?' )
       {
            sentences++;
       }
       else if (isblank(text[i]) || i == len-1 )
       {
            words++;
       }
    }

    // count avarage leters in 100 words
    float avg_letters = (float)letters / (float)words * 100;
    // count avarage sentences in 100 words
    float avg_sentences = (float)sentences / (float)words * 100;
    int index = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8);

    return index;
}
