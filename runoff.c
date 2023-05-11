#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];           // Creates each candidate name
        candidates[i].votes = 0;                    // Sets each candidate vote count to 0
        candidates[i].eliminated = false;           // Creates flag to track if candidate is eliminated
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    bool vote_valid = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            vote_valid = true;
            return vote_valid;
        }
    }

    return vote_valid;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int cand_check;

    // Reset vote counts
    for (int k = 0; k < candidate_count; k++)
    {
        candidates[k].votes = 0;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            cand_check = preferences[i][j];
            if (candidates[cand_check].eliminated == false)
            {
                candidates[cand_check].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int votes_needed = (voter_count / 2) + 1;          // Need over half of the votes to win

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= votes_needed)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize variable to track min number. Start at over the max voters to guarantee it is lowered by one of the values in the array.
    int min = MAX_VOTERS + 1;
    for (int i = 0; i < candidate_count; i++)                                   // Loop through candidates
    {
        if (candidates[i].eliminated == false && candidates[i].votes < min)     // Check if candidate has been eliminated and if candidate votes are less than current value of min
        {
                min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Initialize tracker variable set to false (not tied)
    bool tie_tracker = false;

    // Loop through each candidate's vote count
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            tie_tracker = true;             // flip tracker to true if the the votes value equals the min
        }
        else if (candidates[i].eliminated == false && candidates[i].votes > min)
        {
            tie_tracker = false;            // flip the tracker to false and return false if even one vote value does not equal the min
            return tie_tracker;
        }
    }
    return tie_tracker;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Change eliminated attribute to true for those with votes equaling the min
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}