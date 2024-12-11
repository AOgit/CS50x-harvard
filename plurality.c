#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void selection_sort(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{

    selection_sort();
    printf("%s\n", candidates[0].name);

    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes < candidates[i - 1].votes)
            break;
        printf("%s\n", candidates[i].name);
    }
    return;
}

void selection_sort(void)
{
    candidate curr_candidate[1];
    candidate max_candidate[1];
    int max;
    // Selection sort
    for (int i = 0; i < candidate_count - 1; i++)
    {
        max = i;
        curr_candidate[0] = candidates[i];
        max_candidate[0] = candidates[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > max_candidate[0].votes)
            {
                max = j;
                max_candidate[0] = candidates[j];
            }
        }
        candidates[i] = max_candidate[0];
        candidates[max] = curr_candidate[0];
    }
}
