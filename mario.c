#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input for pyramid height
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build first row of left side of pyramid
    // Build first row of right side of pyramid
    int space_count = height - 2;
    int hash_count = 1;

    int row_count;
    for (row_count = 0; row_count < height; row_count++)
    {
        //create loop to print the spaces
        for (int i = space_count; i >= 0; i--)
        {
            printf(" ");
        }

        //create loop to print the hashes
        for (int j = height - hash_count; j < height; j++)
        {
            printf("#");
        }

        // Print space on row between two pyramid halves
        printf("  ");

        for (int k = height - hash_count; k < height; k++)
        {
            printf("#");
        }
        //print a new line after spaces and hashes are printed
        printf("\n");

        //decrement the spaces by 1 and increment the hashes by 1 for the next row
        space_count--;
        hash_count++;
    }
}