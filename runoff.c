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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
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
    // TODO
    //loops over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //if voted candidate is valid, add to preferences and return true
        if(strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //loops over voters
    for (int i = 0; i < voter_count; i++)
    {
        //loops over voter preferences
        for (int j = 0; j < candidate_count; j++)
        {
            //if vote gets tabulated, loops breaks
            if(!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    //create return variable which is defaulted to false (no winners)
    bool winner = false;
    //loops over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //if candidate votes are greater than majority and not eliminated, print candidate and set return variable to true
        if(candidates[i].votes > (voter_count/2) && !candidates[i].eliminated)
        {
            printf("winner: %s\n",candidates[i].name);
            winner = true;
        }
    }
    return winner;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    //create least votes variable which is default to 100 since maximum voters is 100 and we are looking for least votes
    int least = 100;
    //loops candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //checks if candidate is eliminated, if not, continues to if statement
        if (!candidates[i].eliminated)
        {
            //if the current candidate's votes is less than the current least votes, change the current least votes to the current candidate's amount of votes
            if (candidates[i].votes < least)
            {
                least = candidates[i].votes;
            }
        }
    }
    return least;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    //loops amount of candidates-1
    for (int i = 0; i < candidate_count-1; i++)
    {
        //checks only candidates that are not eliminated
        if (!candidates[i].eliminated & !candidates[i+1].eliminated)
        {
            //if the two uneliminated candidates' vote count doesnt match, return false
            if(candidates[i].votes != candidates[i+1].votes)
            {
                return false;
            }
        }
    }
    //if all remaining candidates' vote counts are the same, return true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    //loops candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //if the candidate's vote count matches the min argument, set the candidate's eliminated varibale to true
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}