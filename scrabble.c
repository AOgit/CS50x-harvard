#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define SIZE = 26;
char chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_points(string str);

int main(void)
{
    string answer1 = get_string("Player 1: ");
    string answer2 = get_string("Player 2: ");

    int result1 = get_points(answer1);
    int result2 = get_points(answer2);

    // Compare received results
    if (result1 > result2)
    {
        printf("Player 1 wins!\n");
    }
    else if (result1 < result2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int get_points(string str)
{

    int summ = 0;

    // Take each char of the string
    for (int i = 0, len = strlen(str); i < len; i++)
    {
        // Iterate over the array of chars
        for (int j = 0; j < 26; j++)
        {
            // summ +=  (str[i] == chars[j]) ? points[j] : 0;
            // Compare char of string and char in array
            if (toupper(str[i]) == chars[j])
            {
                summ += points[j];
                break;
            }
        }
    }
    return summ;
}
