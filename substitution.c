#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype
bool valid_key(string str);
string cipher_text(string key, string str);

int main(int argc, string argv[])
{

    const string key = argv[1];
    // Validate amount of arguments
    if (argc != 2)
    {
        printf("Usage: %s KEY\n", argv[0]);
        return 1;
    }
    // Key validation
    if (!valid_key(key))
        return 1;

    // Plain text
    string plaintext = get_string("plaintext: ");
    // Cipher text
    string ciphertext = cipher_text(key, plaintext);
    printf("ciphertext: %s\n", ciphertext);
}

bool valid_key(string str)
{

    int len = strlen(str);
    int summ_key = 0;
    if (len != 26)
    {
        printf("Key must contain 26 characters\n");
        return false;
    }

    // Validate for alphabetic characters
    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            str[i] = toupper(str[i]);
            // Will be used below to check unique letters
            // summ_key += str[i];
        }
        else
        {
            printf("Key must only contain alphabetic characters\n");
            return false;
        }

        /* // Not working. Look below
        // Validate for Uniq characters
        // Compute summ c decimals code of all capital letters S = (a1+an)*n/2
        // Decimal A = 65, decimal Z = 90
        int summ_cap_letters = (65+90)*26/2;
        if (summ_cap_letters != summ_key)
        {
            printf("Key must not contain repeated characters\n");
            return false;
        }*/
        // Validate for Uniq characters
        for (int j = i + 1; j < len; j++)
        {
            if (toupper(str[i]) == toupper(str[j]))
            {
                printf("Key must not contain multirepeated characters\n");
                return false;
            }
        }
    }

    return true;
}

string cipher_text(string key, string str)
{
    // Initial ciphertext
    string ciphertext = str;

    for (int i = 0, len = strlen(str); i < len; i++)
    {
        if (!isalpha(str[i]))
        {
            ciphertext[i] = str[i];
        }
        else if (isupper(str[i]))
        {
            int key_index = str[i] - 65;
            ciphertext[i] = toupper(key[key_index]);
        }
        else
        {
            int key_index = str[i] - 97;
            ciphertext[i] = tolower(key[key_index]);
        }
    }
    return ciphertext;
}
