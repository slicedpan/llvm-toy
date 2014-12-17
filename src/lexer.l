
%{
#include <stdio.h>
#include <string.h>

void lexer_add_integer(void*, char*);
void lexer_add_float(void*, char*);
void lexer_add_string(void*, char*);
void lexer_add_keyword_def(void*, char*);
void lexer_add_keyword_extern(void* char*);
void lexer_add_operator(void* char);

void* p;

%}

%option noyywrap

%%

[0-9]+ { lexer_add_integer(p, yytext); }

.|\n { }

%%

void lexer_input(char* source, void* userdata) {  
  FILE* f = fmemopen(source, strlen(source), "r");
  yyin = f;
  p = userdata;
  yylex();  
}