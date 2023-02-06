#include <stdio.h>
#include <ctype.h>
#include <string.h>

// E=TR
// R=+TR
// R=$
// T=FY
// Y=*FY
// Y=$
// F=(E)
// F=i

int numOfProductions;
char productionSet[10][10];
// function to add a character to result
void addToResultSet(char Result[], char val)
{
    int k;
    for (k = 0; Result[k] != '\0'; k++)
        if (Result[k] == val)
            return;
    Result[k] = val;
    Result[k + 1] = '\0';
}

// function to find first of a symbol
void FIRST(char *Result, char c)
{
    int i, j, k;
    char subResult[20];
    int foundEpsilon;
    subResult[0] = '\0';
    Result[0] = '\0';
    // If X is terminal, FIRST(X) = {X}.
    if (!(isupper(c)))
    {
        addToResultSet(Result, c);
        return;
    }
    // If X is non terminal
    // Read each production
    for (i = 0; i < numOfProductions; i++)
    {
        // Find production with X as LHS
        if (productionSet[i][0] == c)
        {
            // If X → ε is a production, then add ε to FIRST(X).
            if (productionSet[i][2] == '#')
                addToResultSet(Result, '#');
            // If X is a non-terminal, and X → Y1 Y2 ... Yk
            // is a production, then add a to FIRST(X) if for some i, a is in FIRST(Yi),
            // and ε is in all of FIRST(Y1), ..., FIRST(Yi-1).
            else
            {
                j = 2;
                while (productionSet[i][j] != '\0')
                {
                    foundEpsilon = 0;
                    FIRST(subResult, productionSet[i][j]);
                    // X-> Y ; add first of non terminal Y to the FIRST of X
                    for (k = 0; subResult[k] != '\0'; k++)
                        addToResultSet(Result, subResult[k]);
                    // X-> Y1Y2 ; if first of Y1 has an epsilon, then have to run the for loop again to check FIRST of Y2
                    for (k = 0; subResult[k] != '\0'; k++)
                        if (subResult[k] == '#')
                        {
                            foundEpsilon = 1;
                            break;
                        }
                    // No ε found, no need to check next element
                    if (!foundEpsilon)
                        break;
                    j++;
                }
            }
        }
    }
    return;
}

// function to find follow of an element
void follow(char *Result, char c)
{
    int i, j, k;
    char subResult[20];
    int foundEpsilon;
    subResult[0] = '\0';
    Result[0] = '\0';
    // if start symbol, add $ to result set
    if (productionSet[0][0] == c)
    {
        addToResultSet(Result, '$');
    }
    for (i = 0; i < numOfProductions; i++)
    {
        j = 2;
        // search every symbol in the RHS for a match
        while (productionSet[i][j] != '\0')
        {
            if (productionSet[i][j] == c)
            {
                int limit = 1;
                // A --> pBqrs, then FOLLOW(B) = FIRST(q)
                // if FIRST(q) contains epsilon, then add to FOLLOW(B) FIRST(r)...and so on
                while (productionSet[i][j + limit] != '\0')
                {
                    foundEpsilon = 0;
                    FIRST(subResult, productionSet[i][j + limit]);
                    for (k = 0; subResult[k] != '\0'; k++)
                    {
                        if (subResult[k] != '#')
                            addToResultSet(Result, subResult[k]);
                        else
                        {
                            limit++;
                            foundEpsilon = 1;
                        }
                    }
                    if (foundEpsilon == 0)
                        break;
                }
                // A --> pB or A --> pBqrs and first of q, r, s contains epsilon, then add FOLLOW(A) to FOLLOW(B)
                // provided A!=B
                if (productionSet[i][j + limit] == '\0')
                {
                    subResult[0] = '\0';
                    if (productionSet[i][0] != productionSet[i][j])
                    {
                        follow(subResult, productionSet[i][0]);
                    }
                    for (k = 0; subResult[k] != '\0'; k++)
                        addToResultSet(Result, subResult[k]);
                }
            }
            j++;
        }
    }
}
void main()
{
    int i, k;
    char choice;
    char c;
    char result[20];
    // printf("How many number of productions ? :");
    // scanf(" %d", &numOfProductions);
    numOfProductions = 8;
    strcpy(productionSet[0], "E=TR");
    strcpy(productionSet[1], "R=+TR");
    strcpy(productionSet[2], "R=#");
    strcpy(productionSet[3], "T=FY");
    strcpy(productionSet[4], "Y=*FY");
    strcpy(productionSet[5], "Y=#");
    strcpy(productionSet[6], "F=(E)");
    strcpy(productionSet[7], "F=i");
    // for (i = 0; i < numOfProductions; i++)
    // {
    //     printf("Enter productions Number %d : ", i + 1);
    //     scanf(" %s", productionSet[i]);
    // }
    do
    {
        printf("\nFIRST or FOLLOW:\n1. FIRST\n2. FOLLOW\n");
        scanf("%d", &k);
        switch (k)
        {
        case 1:
            printf("\nFind the FIRST of  :");
            scanf(" %c", &c);
            FIRST(result, c);
            printf("\nFIRST(%c)= { ", c);
            for (i = 0; result[i] != '\0'; i++)
                printf(" %c ", result[i]);
            printf("}\n");
            break;

        case 2:
            printf("\nFind the FOLLOW of  :");
            scanf(" %c", &c);
            follow(result, c);
            printf("\nFOLLOW(%c)= { ", c);
            for (i = 0; result[i] != '\0'; i++)
                printf(" %c ", result[i]);
            printf("}\n");
            break;
        }
        printf("press 'y' to continue : ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
}