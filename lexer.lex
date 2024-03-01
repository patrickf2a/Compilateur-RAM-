%{
#include <string.h>
#include "parser.h"
%}

%option nounput
%option noinput

NOMBRE  (0|[1-9][0-9]*)
IDENT   [a-zA-Z][a-zA-Z0-9]*
COMMENT #.*
%%

"<="               { return INFEGAL; }
">="               { return SUPEGAL; }
ALGO               { return ALGO; }
ENTREE             {return ENTREE;}

VAR                { return VAR; }
TQ                 { return TQ; }
FAIRE              { return FAIRE; }
FTQ                { return FTQ; }
SI                 { return SI; }
ALORS              { return ALORS; }
SINON              { return SINON; }
FSI                { return FSI; }
LIRE               { return LIRE; }
AFFICHER           { return AFFICHER; }
DEBUT              { return DEBUT; }
FIN                { return FIN; }
"<-"               { return AFFECT; }
[)(\[\]+*/=\<\>-]  { return yytext[0]; }
ET                 { return ET; }
OU                 { return OU; }
NON                { return NON; }
{IDENT}            { strcpy(yylval.id, yytext); return ID; }
{NOMBRE}           { yylval.nb = atoi(yytext); return NB; }
{COMMENT}          {}
[ \t]              {}
[\n]               { return NL; }
.                  { fprintf(stderr, "[err lexer] caractere inconnu %c\n",yytext[0]); return 1; }

%%
