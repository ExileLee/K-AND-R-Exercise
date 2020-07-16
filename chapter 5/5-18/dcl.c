#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 1000

enum { NAME, PARENS, BRACKETS };

int dcl(void);
int dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(int argc, char *argv[])
{
    while (gettoken() != EOF)
    {
        strcpy(datatype, token);
        out[0] = '\0';
        int result = dcl();
        if (result)
        {
            if (tokentype != '\n')
                printf("syntax error \n");
            printf("%s: %s %s\n", name, out, datatype);
        }    
    }
    return 0;
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
        
    }   
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';    
        return tokentype = BRACKETS;    
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;    
    }
    else
    {
        return tokentype = c;
    } 
}

int dirdcl(void)
{
    int type;

    if (tokentype == '(')
    {
        int dclResult = dcl();
        if (!dclResult)
        {
            return 0;
        }
        if (tokentype != ')')
        {
            printf("error: missing )\n");
            return 0;
        }
    }
    else if (tokentype == NAME)
    {
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        return 0;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " arrary");
            strcat(out, token);
            strcat(out, " of");
        }
    }

    return 1;
}

int dcl()
{
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;
    int result = dirdcl();
    while (ns-- > 0 && result)
    {
        strcat(out, " pointer to");
    }

    return result;    
}


int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many chars");
    else
        buf[bufp++] = c;
}