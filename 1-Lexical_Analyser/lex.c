#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

bool isKeyword(char keyWords[32][20], char *s)
{
    for (int i = 0; i < 32; ++i)
    {
        if (strcmp(s, keyWords[i]) == 0)
            return true;
    }
    return false;
}

bool isFunction(char *s)
{
    if (strcmp(s, "printf") == 0 || strcmp(s, "scanf") == 0 || strcmp(s, "main") == 0)
        return true;
    return false;
}

int main()
{
    char keyWords[32][20] =
        {"auto", "break", "case", "char", "const", "continue", "default", "do",
         "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
         "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
         "unsigned", "void", "volatile", "while"};

    char fileName[100];
    printf("Enter file name : ");
    scanf("%s", fileName);
    FILE *fptr = fopen(fileName, "r");
    int k, id = 0, lc = 1;
    char c;
    printf("%-5s %-15s %-25s %-10s\n", "S.No", "Token", "Lexeme", "Line No");
    printf("---------------------------------------------------------------\n");
    while ((c = fgetc(fptr)) != EOF)
    {
        char buffer[24];
        k = 0;
        if (isalpha(c))
        {
            buffer[k++] = c;
            while ((c = fgetc(fptr)) != EOF && isalpha(c))
            {
                buffer[k++] = c;
            }
            buffer[k] = '\0';
            if (isKeyword(keyWords, buffer))
                printf("%-5d %-15s %-25s %-10d\n", id++, "keyword", buffer, lc);
            else if (isFunction(buffer))
                printf("%-5d %-15s %-25s %-10d\n", id++, "function", buffer, lc);
            else
                printf("%-5d %-15s %-25s %-10d\n", id++, "identifier", buffer, lc);
        }
        if (c == EOF)
            break;
        if (isdigit(c))
        {
            buffer[k++] = c;
            while ((c = fgetc(fptr)) != EOF && isdigit(c))
            {
                buffer[k++] = c;
            }
            buffer[k] = '\0';
            printf("%-5d %-15s %-25s %-10d\n", id++, "number", buffer, lc);
        }

        if (c == EOF)
            break;
        if (c == '(' || c == ')')
            printf("%-5d %-15s %-25c %-10d\n", id++, "parenthesis", c, lc);
        if (c == '{' || c == '}')
            printf("%-5d %-15s %-25c %-10d\n", id++, "brace", c, lc);
        if (c == '[' || c == ']')
            printf("%-5d %-15s %-25c %-10d\n", id++, "arrayIndex", c, lc);
        if (c == ',' || c == ';')
            printf("%-5d %-15s %-25c %-10d\n", id++, "punctuation", c, lc);
        if (c == '"')
        {
            while ((c = fgetc(fptr)) != EOF && c != '"')
            {
                buffer[k++] = c;
            }
            buffer[k] = '\0';
            printf("%-5d %-15s %-25s %-10d\n", id++, "string", buffer, lc);
        }
        if (c != EOF && c == '\n')
            lc++;
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '>' || c == '<' || c == '=' || c == '&' || c == '|' || c == '!')
            printf("%-5d %-15s %-25c %-10d\n", id++, "operator", c, lc);
    }
    fclose(fptr);
    return 0;
}

// Output:
/* 

Enter file name : input.c
S.No  Token           Lexeme                    Line No   
---------------------------------------------------------------
0     identifier      include                   1
1     operator        <                         1
2     identifier      stdio                     1
3     identifier      h                         1
4     operator        >                         1
5     keyword         int                       2
6     function        main                      2
7     parenthesis     (                         2
8     parenthesis     )                         2
9     brace           {                         3
10    function        printf                    4
11    parenthesis     (                         4
12    string          Hello World!              4
13    parenthesis     )                         4
14    punctuation     ;                         4
15    brace           }                         5

 */