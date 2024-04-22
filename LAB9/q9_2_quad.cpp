/*
Write a program to generate 3 address codes along with quadruples, triples, and indirect triples
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void small();
void dove(int i);
int p[5] = {0, 1, 2, 3, 4}, c = 1, i, k, l, m, pi;
char sw[5] = {'=', '-', '+', '/', '*'}, j[20], a[5], b[5], ch[2];
int ctr = 0;

int main()
{
    printf("Enter the expression:");
    scanf("%s", j);
    // printf("\tThe Intermediate code is:\n");
    printf("# \t Op \t Arg1 \t Arg2 \t Result\n", ctr, a, b, c);
    small();

    return 0;
}
void dove(int i)
{
    a[0] = b[0] = '\0';
    if (!isdigit(j[i + 2]) && !isdigit(j[i - 2]))
    {
        a[0] = j[i - 1];
        b[0] = j[i + 1];
    }
    if (isdigit(j[i + 2]))
    {
        a[0] = j[i - 1];
        b[0] = 't';
        b[1] = j[i + 2];
    }
    if (isdigit(j[i - 2]))
    {
        b[0] = j[i + 1];
        a[0] = 't';
        a[1] = j[i - 2];
        b[1] = '\0';
    }
    if (isdigit(j[i + 2]) && isdigit(j[i - 2]))
    {
        a[0] = 't';
        b[0] = 't';
        a[1] = j[i - 2];
        b[1] = j[i + 2];
        sprintf(ch, "%d", c);
        j[i + 2] = j[i - 2] = ch[0];
    }
    if (j[i] == '*')
        // printf("\tt%d=%s*%s\n", c, a, b);
        printf("(%d) \t * \t %s \t %s \t t%d\n", ctr, a, b, c);

    if (j[i] == '/')
        // printf("\tt%d=%s/%s\n", c, a, b);
        printf("(%d) \t / \t %s \t %s \t t%d\n", ctr, a, b, c);

    if (j[i] == '+')
        // printf("\tt%d=%s+%s\n", c, a, b);
        printf("(%d) \t + \t %s \t %s \t t%d\n", ctr, a, b, c);

    if (j[i] == '-')
        // printf("\tt%d=%s-%s\n", c, a, b);
        printf("(%d) \t - \t %s \t %s \t t%d\n", ctr, a, b, c);
    if (j[i] == '=')
        // printf("\t%c=t%d", j[i - 1], --c);
        printf("(%d) \t = \t t%d \t %s \t %c\n", ctr, --c, "", j[i - 1]);

    sprintf(ch, "%d", c);
    j[i] = ch[0];
    c++;
    ctr++;
    small();
}
void small()
{
    pi = 0;
    l = 0;
    for (i = 0; i < strlen(j); i++)
    {
        for (m = 0; m < 5; m++)
            if (j[i] == sw[m])
                if (pi <= p[m])
                {
                    pi = p[m];
                    l = 1;
                    k = i;
                }
    }
    if (l == 1)
        dove(k);
    else
        exit(0);
}