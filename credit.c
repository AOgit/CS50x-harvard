#include <cs50.h>
#include <stdio.h>


int main (void)
{
    long n;
    // get card number and initial check range
    do
    {
        n = get_long ("Number: ");
    }
    while (n < 4000000000000 || n > 5500000000000000);
    // printf ("%li\n", n);

    long rest_number=n;
    int last_digit;
    bool odd = true;
    int  counter = 0;
    int  sum_odd = 0;
    int  even_number = 0;
    int  sum_even = 0;
    int first_digit;
    int first_2_digits;

    // using Luhn’s Algorithm
    while (rest_number > 0)
    {
        last_digit = rest_number % 10;
        if (odd)
        {
            sum_odd += last_digit;
            odd = false;
        }
        else
        {
            even_number = last_digit*2;
            if (even_number > 9)
            {
                sum_even += 1 + even_number % 10;
            }
            else
            {
                sum_even += even_number;
            }
            odd = true;
        }
        // printf for debugging
        // printf("last_digit: %i, rest_number: %li, sum_odd: %i, even_number %i, sum_even %i\n", last_digit, rest_number, sum_odd, even_number, sum_even);

        // get first or first 2 digits of card number for next check
        if (rest_number > 9 && rest_number < 100 )
        {
             first_2_digits = rest_number;
        }
        else if (rest_number < 10)
        {
             first_digit = rest_number;
        }

        rest_number = rest_number / 10;
        counter++;
    }
    // check using Luhn’s Algorithm
    int check_digit = (sum_odd + sum_even) % 10;

    // printf for debugging
    // printf("first_2_digits: %i, first_digit: %i, counter: %i\n", first_2_digits, first_digit, counter);

    // final check and card type determination
    if (check_digit != 0)
    {
        printf("INVALID\n");
    }
    else if (counter == 15 && (first_2_digits == 34 || first_2_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (counter == 16 && (first_2_digits == 51 || first_2_digits == 52 || first_2_digits == 53 || first_2_digits == 54 || first_2_digits == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((counter == 16 || counter == 13) && (first_digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
