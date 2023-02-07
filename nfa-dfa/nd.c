#include <stdio.h>
#include <string.h>
int i = 0, j = 0, end;
struct dfastates
{
    char state[10];
    int check;
};
struct dfastates st[10];
int notin(char s[], struct dfastates st[], int limit)
{
    for (int k = 0; k < limit; k++)
    {
        if (strcmp(st[k].state, s) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int checkdup(char state[], char states[10][10], int limit)
{
    for (int k = 0; k < limit; k++)
    {
        if (strcmp(state, states[k]) == 0)
            return 1;
    }
    return 0;
}
void main()
{
    FILE *f1;
    char state[10], input0[10], input1[10], delim[] = ",";
    f1 = fopen("nfa.txt", "r");
    printf("The converted DFA is:\n");
    printf("STATE1\t\tinput\t\tSTATE2\n");
    end = fscanf(f1, "%s %s %s", state, input0, input1);
    if (notin(state, st, i) == 1)
    {
        strcpy(st[i].state, state);
        st[i].check = 1;
        j++;
        i++;
    }
    if (strcmp(input0, "-") != 0 && notin(input0, st, i) == 1)
    {
        strcpy(st[i].state, input0);
        st[i].check = 0;
        i++;
    }
    if (strcmp(input1, "-") != 0 && notin(input1, st, i) == 1)
    {
        strcpy(st[i].state, input1);
        st[i].check = 0;
        i++;
    }
    printf("%s\t\t%s\t\t%s\n", state, input0, input1);
    while (j < i)
    {
        if (st[j].check == 0)
        {
            printf("%s\t\t", st[j].state);
            char copy[10], result0[20], result1[20];
            int res0 = 0, res1 = 0;
            strcpy(copy, st[j].state);
            char *ptr = strtok(copy, delim);
            while (ptr != NULL)
            {
                rewind(f1);
                end = fscanf(f1, "%s %s %s", state, input0, input1);
                while (end != EOF)
                {
                    if (strcmp(state, ptr) == 0)
                    {
                        if (res0 == 0 && strcmp(input0, "-") != 0)
                        {
                            strcpy(result0, input0);
                            res0++;
                        }
                        else if (strcmp(input0, "-") != 0)
                        {
                            strcat(result0, ",");
                            strcat(result0, input0);
                        }
                        if (res1 == 0 && strcmp(input1, "-") != 0)
                        {
                            strcpy(result1, input1);
                            res1++;
                        }
                        else if (strcmp(input1, "-") != 0)
                        {
                            strcat(result1, ",");
                            strcat(result1, input1);
                        }
                    }
                    end = fscanf(f1, "%s %s %s", state, input0, input1);
                }
                ptr = strtok(NULL, delim);
            }
            st[j].check = 1;
            j++;
            char copy0[10][10], copy1[10][10], dupremove[10];
            // Remove the duplicates generated while concatenating
            char *ptr0 = strtok(result0, delim);
            int count = 0;
            while (ptr0 != NULL)
            {
                if (checkdup(ptr0, copy0, count) == 0)
                {
                    strcpy(copy0[count], ptr0);
                    count++;
                }
                ptr0 = strtok(NULL, delim);
            }
            strcpy(dupremove, copy0[0]);
            for (int k = 1; k < count; k++)
            {
                strcat(dupremove, ",");
                strcat(dupremove, copy0[k]);
            }
            printf("%s\t\t", dupremove);
            if (notin(dupremove, st, i) == 1)
            {
                strcpy(st[i].state, dupremove);
                st[i].check = 0;
                i++;
            }
            char *ptr1 = strtok(result1, delim);
            count = 0;
            while (ptr1 != NULL)
            {
                if (checkdup(ptr1, copy1, count) == 0)
                {
                    strcpy(copy1[count], ptr1);
                    count++;
                }
                ptr1 = strtok(NULL, delim);
            }
            strcpy(dupremove, copy1[0]);
            for (int k = 1; k < count; k++)
            {
                strcat(dupremove, ",");
                strcat(dupremove, copy1[k]);
            }
            printf("%s\n", dupremove);
            if (notin(dupremove, st, i) == 1)
            {
                strcpy(st[i].state, dupremove);
                st[i].check = 0;
                i++;
            }
        }
    }
}