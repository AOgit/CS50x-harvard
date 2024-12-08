#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool all_digits(string arg);
string rotate(int KEY, string str);

int main(int argc, string argv[])
{
    // Check for amount of arguments and all digits
    if (argc != 2 || !all_digits(argv[1]))
    {
        return 1;
    }

    int KEY = atoi(argv[1]) % 26;

    string plaintext = get_string("plaintext: ");

    // Get Caesar ciphertext
    string ciphertext = rotate(KEY, plaintext);

    // Printing output
    printf("ciphertext: %s\n", ciphertext);
}

bool all_digits(string arg)
{
    for (int i = 0, len = strlen(arg); i < len; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
            return false;
    }
    return true;
}

string rotate(int KEY, string str)
{
    // Initial ciphertext
    string ciphertext = str;
    for (int i = 0, len = strlen(str); i < len; i++)
    {
        // Rotate only letters
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            ciphertext[i] = ('z' - str[i] >= KEY) ? str[i] + KEY : 'a' + (KEY - ('z' - str[i]) - 1);
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            ciphertext[i] = ('Z' - str[i] >= KEY) ? str[i] + KEY : 'A' + (KEY - ('Z' - str[i]) - 1);
        }
    }
    return ciphertext;
}
