#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int winnernumber;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        int found = strcmp(name, candidates[i]);
        if (found == 0)
        {
            ranks[rank] = i;
            //printf("%i %i\n", rank, i);
            /*
            for (int j = 0; j < candidate_count; j++)
            {
                printf("%i \n", ranks[j]);
            }
            */
            return true;
        }


    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }

    }
    //
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //printf("%i ", preferences[ranks[i]][k]);
            //printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    //
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int m = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[m].winner = i;
                pairs[m].loser = j;
                //printf("OK %i %i\n", pairs[m].winner, pairs[m].loser);
                m++;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[m].winner = j;
                pairs[m].loser = i;
                //printf("OK %i %i\n", pairs[m].winner, pairs[m].loser);
                m++;
                pair_count++;

            }
        }
    }
    printf("\n");
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /*
    for (int i = 0; i < (candidate_count * ((candidate_count - 1)) / 2); i++)
    {
        printf("%i %i\n", pairs[i].winner, pairs[i].loser);
    }
    */
    pair pairtemp;
    bool sorted = false;

    while (sorted == false)
    {
        sorted = true;
        for (int i = ((candidate_count * ((candidate_count - 1)) / 2) - 1); i > 0; i--)
        {

            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {

                pairtemp = pairs[i - 1];
                pairs[i - 1] = pairs[i];
                pairs[i] = pairtemp;
                sorted = false;

            }
        }

    }
/*
    for (int i = 0; i < (candidate_count * ((candidate_count - 1)) / 2); i++)
    {
        printf("%i %i\n", pairs[i].winner, pairs[i].loser);
    }
*/
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int arrows[candidate_count];
    int column_zero = 0;

    // filling locked array
    for (int k = 0; k < pair_count; k++)
    {
        locked[pairs[k].winner][pairs[k].loser] = true;
        locked[pairs[k].loser][pairs[k].winner] = false;
        for (int i = 0; i < candidate_count; i++)
        {
            arrows[i] = 0;
        }
        //calculating number of 1 in a column (every candidate)
        for (int j = 0; j < candidate_count; j++)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (locked[i][j] == 1)
                {
                    arrows[j]++;
                }
            }
        }

        column_zero = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (arrows[i] == 0)
            {
                column_zero++;
            }
            printf("%i %i ok \n", column_zero, i);

        }
        printf("%i OUT \n",column_zero);
        if (column_zero == 0)
        {
            locked[pairs[k].winner][pairs[k].loser] = false;
            locked[pairs[k].loser][pairs[k].winner] = false;
            column_zero++;
        }
        for (int i = 0; i < candidate_count; i++)
        {
            if (arrows[i] == 0)
            {
                winnernumber = i;
            }
        }
    }

/*
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < candidate_count; i++)
    {
        printf("%i \n", arrows[i]);
    }
*/
    return;
}

// Print the winner of the election
void print_winner(void)
{
    printf("%s\n", candidates[winnernumber]);
    return;
}

