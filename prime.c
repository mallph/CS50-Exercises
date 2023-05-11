#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    //initialize a divisor to test and increment
    int divisor = 2;

    //initialize a remainder variable
    int remainder;

    //initialize a variable to determine if a number is still prime
    bool prime_indicator = true;

    //while loop to test each divisor
    while ((divisor < number) && prime_indicator == true)
    {
        //check the remainder of dividing the number by the current divisor
        remainder = number % divisor;

        //indicate a number is not prime if a divisor goes into it evenly
        if (remainder == 0)
        {
            prime_indicator = false;
        }

        //if the number cannot be divided by the divisor evenly, increment to check the next divisor
        else
        {
            divisor++;
        }
    }
    return prime_indicator;
}
