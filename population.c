#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Enter a start size greater than 9: ");
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("Enter an ending population size greater than the start: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int n = start_size;
    int years = 0;
    do
    {
        n = n + (n / 3) - (n / 4);
        years++;
    }
    while (n < end_size);

    // TODO: Print number of years
    if (start_size == end_size)
    {
        printf("Years: 0");
    }
    else
    {
        printf("Years: %i\n", years);
    }

}
