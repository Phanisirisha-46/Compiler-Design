#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *str)
{
    char k[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                      "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
                      "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
                      "unsigned", "void", "volatile", "while"};
    int i;
    for (i = 0; i < 32; i++)
        if (strcmp(k[i], str) == 0)
            return 1;
    return 0;
}

int isFunction(char *str)
{
    if (strcmp(str, "main") == 0 || strcmp(str, "printf") == 0)
        return 1;
    return 0;
}

int main()
{
    int kc, lno = 1, sno = 0;
    char fn[20], c, buf[30];
    FILE *fp;

    printf("\nEnter the file name: ");
    scanf("%s", fn);

    printf("\n\nS.No\tToken\tLexeme\tLine No");
    fp = fopen(fn, "r");
    if (!fp)
    {
        printf("\nError: File not found!");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF)
    {
        if (isalpha(c))
        {
            buf[kc = 0] = c;
            while (isalnum(c = fgetc(fp)))
            {
                buf[++kc] = c;
            }
            buf[++kc] = '\0';
            if (isKeyword(buf))
                printf("\n%4d\tKeyword\t%7s\t%7d", ++sno, buf, lno);
            else if (isFunction(buf))
                printf("\n%4d\tFunction\t%7s\t%7d", ++sno, buf, lno);
            else
                printf("\n%4d\tIdentifier\t%7s\t%7d", ++sno, buf, lno);
        }
        else if (isdigit(c))
        {
            buf[kc = 0] = c;
            while (isdigit(c = fgetc(fp)))
                buf[++kc] = c;
            buf[++kc] = '\0';
            printf("\n%4d\tNumber\t%7s\t%7d", ++sno, buf, lno);
        }
        else if (c == '(' || c == ')')
            printf("\n%4d\tParenthesis\t%6c\t%7d", ++sno, c, lno);
        else if (c == '{' || c == '}')
            printf("\n%4d\tBrace\t%6c\t%7d", ++sno, c, lno);
        else if (c == '[' || c == ']')
            printf("\n%4d\tArray Index\t%6c\t%7d", ++sno, c, lno);
        else if (c == ',' || c == ';')
            printf("\n%4d\tPunctuation\t%6c\t%7d", ++sno, c, lno);
        else if (c == '"')
        {
            kc = -1;
            while ((c = fgetc(fp)) != '"')
                buf[++kc] = c;
            buf[++kc] = '\0';
            printf("\n%4d\tString\t%7s\t%7d", ++sno, buf, lno);
        }
        else if (c == ' ' || c == '\t')
        {
            continue;
        }
        else if (c == '\n')
        {
            ++lno;
        }
        else
        {
            printf("\n%4d\tOperator\t%6c\t%7d", ++sno, c, lno);
        }
    }

    fclose(fp);
    return 0;
}