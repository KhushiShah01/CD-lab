// shift-reduce parser
// The chosen grammar is
//(1)E' → E
//(2)E → aEa
//(3)E → b

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, c, flag = 1, k = 0;
char a[16], stk[15];
char symbols[] = {'a', 'b', '$', 'E'};

struct parsing_table
{
    char action[10];
    int state;
};
struct parsing_table table[10][10];

// function to find the index of the character
int findindex(char c)
{
    for (int i = 0; i < 4; i++)
    {
        if (c == symbols[i])
        {
            return i;
        }
    }
    return -1;
}

// function for goto
void gotofunc()
{
    int table_y = findindex(stk[k]);
    int table_x = stk[k - 1] - '0';
    if (strcmp(table[table_x][table_y].action, "goto") == 0)
    {
        stk[++k] = table[table_x][table_y].state + '0';
    }
    else
    {
        printf("Error in function!");
        exit(0);
    }
}

// function to determine what action to perform
void take_action(int index)
{
    printf("\n%s\t\t%s\t\t", stk, a);
    int table_y = findindex(a[index]);
    int table_x = stk[k] - '0';
    if (strcmp(table[table_x][table_y].action, "accept") == 0)
    {
        printf("Accept");
        flag = 1;
        return;
    }
    else if (strcmp(table[table_x][table_y].action, "shift") == 0)
    {
        stk[++k] = a[index];
        stk[++k] = table[table_x][table_y].state + '0';
        a[index] = ' ';
        printf("Shift to state %d", table[table_x][table_y].state);
    }
    else if (strcmp(table[table_x][table_y].action, "reduce") == 0)
    {
        if (table[table_x][table_y].state == 2)
        {
            for (int l = 0; l < 5; l++)
            {
                stk[k] = ' ';
                k--;
            }
            stk[k] = 'E';
            printf("REDUCE E --> aEa\n");
            gotofunc();
            take_action(index);
        }
        else if (table[table_x][table_y].state == 3)
        {
            stk[k] = ' ';
            k = k - 1;
            stk[k] = 'E';
            printf("REDUCE E --> b\n");
            gotofunc();
            take_action(index);
        }
    }
    else
    {
        printf("ERROR!\n");
        flag = 0;
        return;
    }
}

int main()
{
    char *in_str;
    printf("GRAMMAR is -\nE->aEa \nE->b\n");
    //      (0) (1) (2) (3)
    //      a    b   $ | E
    // 0    s2  s3     | 1
    // 1            ac |
    // 2    s2 s3      | 4  
    // 3    r3      r3 |
    // 4    s5         |
    // 5    r2      r2 |
    // Initialize parsing table with values
    strcpy(table[0][0].action, "shift");
    table[0][0].state = 2;
    strcpy(table[0][1].action, "shift");
    table[0][1].state = 3;
    strcpy(table[0][3].action, "goto");
    table[0][3].state = 1;
    strcpy(table[1][2].action, "accept");
    table[1][2].state = 0;
    strcpy(table[2][0].action, "shift");
    table[2][0].state = 2;
    strcpy(table[2][1].action, "shift");
    table[2][1].state = 3;
    strcpy(table[2][3].action, "goto");
    table[2][3].state = 4;
    strcpy(table[3][0].action, "reduce");
    table[3][0].state = 3;
    strcpy(table[3][2].action, "reduce");
    table[3][2].state = 3;
    strcpy(table[4][0].action, "shift");
    table[4][0].state = 5;
    strcpy(table[5][0].action, "reduce");
    table[5][0].state = 2;
    strcpy(table[5][2].action, "reduce");
    table[5][2].state = 2;
    printf("Enter input string:\t");
    scanf("%s", in_str);
    strcpy(a, strcat(in_str, "$"));
    c = strlen(a);
    stk[k] = '0';
    printf("\nstack \t\t input \t\t action");

    for (i = 0; i < c; i++)
    {
        // print the values of stack and input
        take_action(i);
        if (flag == 0)
            break;
    }

    // if top of the stack is E(starting symbol), then it will accept the input
    if (flag == 1)
        printf("\nString accepted successfully\n");
    else
        printf("\nString rejected\n");

    return 0;
}