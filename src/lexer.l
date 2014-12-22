
%{
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
namespace LexerFunctions {
#endif

void add_integer(void*, char*);
void add_float(void*, char*);
void add_string(void*, char*);
void add_keyword_def(void*, char*);
void add_keyword_extern(void*, char*);
void add_operator(void*, char*);
void add_identifier(void*, char*);

#ifdef __cplusplus
}
#endif

void* p;

%}


DIGIT [0-9]
ALPHANUMERIC [a-zA-Z0-9]
%option noyywrap

%%

{DIGIT}+ { LexerFunctions::add_integer(p, yytext); }
def { LexerFunctions::add_keyword_def(p, yytext); }
extern { LexerFunctions::add_keyword_extern(p, yytext); }
"+"|"-"|"/"|"*"|"=" { LexerFunctions::add_operator(p, yytext); }
\"[^\"]\" { LexerFunctions::add_string(p, yytext); }
{ALPHANUMERIC}+ { LexerFunctions::add_identifier(p, yytext); }
[\n\r]+ { }



%%

#ifdef __cplusplus
namespace LexerFunctions {
#endif

void input(char* source, void* userdata) {  
  FILE* f = fmemopen(source, strlen(source), "r");
  yyin = f;
  p = userdata;
  yylex();  
}

#ifdef __cplusplus
}
#endif