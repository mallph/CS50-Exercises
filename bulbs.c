#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get user input
    string text = get_string("Message: ");

    // Get length of string
    int len = strlen(text);

    // Loop through each letter
    for (int i = 0; i < len; i++)
    {
        // DEBUG: Check ASCII value of the character
        // printf("Value: %i\n", text[i]);

        // Initialize an array for the the bits
        int bit_array[] = {0, 0, 0, 0, 0, 0, 0, 0};

        // Store ASCII value of current character in a variable
        int number = text[i];

        // Convert decimal to binary
        // Start by initializig a counter for going through the array
        int counter = 0;

        // Create loop that uses modulo 2 and then divides number by 2. Note that modulo 2 will only return either 0 or 1
        // Also keep in mind that this loop is working in reverse to how binary is displayed
        while (number > 0)
        {
            bit_array[counter] = number % 2;
            number = number / 2;
            counter++;
        }

        // Print the binary (but remember it is in reverse). j is initialized to 7 because there are 8 bits per byte. Could use a variable for this to make it easier to change
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(bit_array[j]);
        }

        // Print newline for the next character to be looped through
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
