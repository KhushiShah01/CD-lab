#include <stdio.h>
#include <string.h>

char result[10][10], copy[3], states[20][20], alphabets[20][20];
int ind = 0;

int notin(char state[3], char arraytrans[10][10], int limit)
{
    for (int i = 0; i < limit; i++)
    {
        if (strcmp(arraytrans[i], state) == 0)
            return 0;
    }
    return 1;
}

int main()
{
    FILE *INPUT1, *INPUT2, *INPUT3;
    INPUT1 = fopen("input_enfa.txt", "r");
    INPUT2 = fopen("eclosure.txt", "r");
    INPUT3 = fopen("eclosure.txt ", "r");
    char state[3];
    int end1, end2, i = 0, n, k = 0, nalp;
    char state1[3], input[3], state2[3];
    printf("Enter the no of states: ");
    scanf("%d", &n);
    printf("Enter the states:\n");
    for (k = 0; k < n; k++)
        scanf("%s", states[k]);
    printf("Enter number of alphabets: ");
    scanf("%d", &nalp);
    printf("Enter the alphabets: ");
    for (k = 0; k < nalp; k++)
        scanf("%s", alphabets[k]);
    printf("The corresponding nfa without epsilon is:\n");
    printf("STATE\t\tINPUT\t\tSTATES\n");
    for (k = 0; k < n; k++)
    {
        char epclosure[4][10];
        char transition[10][10];
        int q = 0;
        end1 = fscanf(INPUT2, "%s %s %s %s", epclosure[0], epclosure[1], epclosure[2], epclosure[3]);
        if (end1 == EOF)
            break;
        // for each alphabet
        for (int i = 0; i < nalp; i++)
        {
            printf("%s\t\t%s\t\t", states[k], alphabets[i]);
            // for each eclosure
            for (int j = 0; j < n; j++)
            {
                if (strcmp(epclosure[j], "-") != 0)
                {
                    while (1)
                    {
                        end2 = fscanf(INPUT1, "%s %s %s", state1, input, state2);
                        if (end2 == EOF)
                            break;
                        if (strcmp(state1, epclosure[j]) == 0 && strcmp(input, alphabets[i]) == 0 && notin(state2, transition, q) != 0)
                        {
                            strcpy(transition[q], state2);
                            q++;
                        }
                    }
                    rewind(INPUT1);
                }
            }
            // for each element in transition
            for (int j = 0; j < q; j++)
            {
                char fstates[10][10];
                while (1)
                {
                    int isover = fscanf(INPUT3, "%s %s %s %s", fstates[0], fstates[1], fstates[2], fstates[3]);
                    if (isover == EOF)
                        break;
                    if (strcmp(transition[j], fstates[0]) == 0)
                    {
                        for (int a = 0; a < n; a++)
                        {
                            if (strcmp(fstates[a], "-") != 0 && notin(fstates[a], result, ind) != 0)
                            {
                                strcpy(result[ind], fstates[a]);
                                ind++;
                                printf("%s ", fstates[a]);
                            }
                        }
                    }
                }
                rewind(INPUT3);
            }
            if (ind == 0)
                printf("empty set");
            printf("\n");
            for (int j = 0; j < ind; j++)
                strcpy(result[j], " ");
            ind = 0;
        }
    }
    return 0;
}