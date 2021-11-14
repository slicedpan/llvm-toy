
%{

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
namespace LexerFunctions {
#endif


void add_keyword_var(void*, char*, int);

void add_keyword_return_empty(void*, char*, int);

void add_keyword_return(void*, char*, int);

void add_keyword_function(void*, char*, int);

void add_keyword_break(void*, char*, int);

void add_keyword_for(void*, char*, int);

void add_keyword_if(void*, char*, int);

void add_keyword_else(void*, char*, int);

void add_boolean(void*, char*, int);

void add_floating_point(void*, char*, int);

void add_integer(void*, char*, int);

void add_operator_double_equals(void*, char*, int);

void add_operator_equals(void*, char*, int);

void add_operator_plus(void*, char*, int);

void add_operator_minus(void*, char*, int);

void add_operator_not(void*, char*, int);

void add_operator_multiply(void*, char*, int);

void add_operator_divide(void*, char*, int);

void add_comma(void*, char*, int);

void add_string(void*, char*, int);

void add_left_brace(void*, char*, int);

void add_right_brace(void*, char*, int);

void add_left_paren(void*, char*, int);

void add_right_paren(void*, char*, int);

void add_identifier(void*, char*, int);


#ifdef __cplusplus
}
#endif

void* p;
  
%}
  
DIGIT [0-9]
ALPHANUMERIC [a-zA-Z0-9]
%option noyywrap yylineno

%%


var { LexerFunctions::add_keyword_var(p, yytext, yylineno); }

"return"[ \t]*\n { LexerFunctions::add_keyword_return_empty(p, yytext, yylineno); }

return { LexerFunctions::add_keyword_return(p, yytext, yylineno); }

function { LexerFunctions::add_keyword_function(p, yytext, yylineno); }

break { LexerFunctions::add_keyword_break(p, yytext, yylineno); }

for { LexerFunctions::add_keyword_for(p, yytext, yylineno); }

if { LexerFunctions::add_keyword_if(p, yytext, yylineno); }

else { LexerFunctions::add_keyword_else(p, yytext, yylineno); }

true|false { LexerFunctions::add_boolean(p, yytext, yylineno); }

{DIGIT}+.{DIGIT}+ { LexerFunctions::add_floating_point(p, yytext, yylineno); }

{DIGIT}+ { LexerFunctions::add_integer(p, yytext, yylineno); }

== { LexerFunctions::add_operator_double_equals(p, yytext, yylineno); }

= { LexerFunctions::add_operator_equals(p, yytext, yylineno); }

\+ { LexerFunctions::add_operator_plus(p, yytext, yylineno); }

- { LexerFunctions::add_operator_minus(p, yytext, yylineno); }

! { LexerFunctions::add_operator_not(p, yytext, yylineno); }

\* { LexerFunctions::add_operator_multiply(p, yytext, yylineno); }

\/ { LexerFunctions::add_operator_divide(p, yytext, yylineno); }

, { LexerFunctions::add_comma(p, yytext, yylineno); }

\"(\\.|[^"])*\" { LexerFunctions::add_string(p, yytext, yylineno); }

\{ { LexerFunctions::add_left_brace(p, yytext, yylineno); }

\} { LexerFunctions::add_right_brace(p, yytext, yylineno); }

\( { LexerFunctions::add_left_paren(p, yytext, yylineno); }

\) { LexerFunctions::add_right_paren(p, yytext, yylineno); }

{ALPHANUMERIC}+ { LexerFunctions::add_identifier(p, yytext, yylineno); }


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