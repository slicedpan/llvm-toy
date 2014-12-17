 
%{
#include <stdio.h>
void found_integer(char*);
%}
 
%option noyywrap
 
%%

[0-9]+  {         
            found_integer(yytext);
        }
 
.|\n    { }
 
%%

void found_integer(char* txt) {
  printf("Found integer: %s\n", txt);
}
 
int main(void)
{
    /* Call the lexer, then quit. */
    yylex();
    return 0;
}