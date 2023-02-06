#include <stdio.h>
#include <string.h>
char result[20][5], states[20][5], copy[3], st[3];
void addState(char s[3], int idx) // Adds a state to the result
{
    strcpy(result[idx], s);
}
void Display(int idx) // Function to display the Epsilon Closure of a state
{
    int i = 0;
    printf("\nEpsilon closure of %s = { ", copy);
    while (i < idx)
    {
        printf("%s ", result[i]);
        i++;
    }
    printf("}\n");
}
void main()
{
    int n, end;
    FILE *fp;
    char state1[3], state2[3], input[3];
    printf("\nEnter the no. of states: ");
    scanf("%d", &n);
    printf("\nEnter the states:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);
    fp = fopen("transitions.txt", "r");
    if (fp != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            int index = 0;
            strcpy(copy, states[i]);
            strcpy(st, states[i]);
            addState(st, index);
            index++;
            while (1) // Finding the epsilon closure for a state
            {
                end = fscanf(fp, "%s%s%s", &state1, &input, &state2);
                if (end == EOF)
                    break;
                if (strcmp(state1, st) == 0)
                {
                    if (strcmp(input, "e") == 0)
                    {
                        strcpy(st, state2);
                        addState(st, index);
                        index++;
                    }
                }
            }
            Display(index);
            rewind(fp);
        }
    }
    else
        printf("\nError in opening the file.");
}