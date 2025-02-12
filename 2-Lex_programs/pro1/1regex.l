%{
    #include<stdio.h>
    int res = 0;
%}
%%
[\n] {
    res==1?printf("Valid String\n"):printf("Invalid String\n");
}
^a[a|b]*$ {res = 1;}
. res = 0;
%%
int main(){
    printf("Enter the string: ");
    yylex();
    return 0;
}