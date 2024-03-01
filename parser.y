%{
  #include <stdio.h>
  #include <ctype.h>
  #include <unistd.h>

  #include "asa.h"
  #include "ts.h"

  extern int yylex();

%}

%union{
  int nb;
  char id[64];
  struct asa * noeud;
 };

%define "parse.error" "verbose"

%token NL VAR TQ FTQ FAIRE SI ALORS SINON FSI LIRE AFFICHER DEBUT FIN ENTREE ALGO

%token <id> ID
%token <nb> NB
%type <noeud> EXP INSTS INST LVAL l_entree

%right AFFECT
%left OU
%left ET
%left '='
%left '<' '>' INFEGAL SUPEGAL
%left '+' '-' NON
%left '*' '/'

%start PROG

%%

PROG : ALGO ID NL
ENTREE l_entree NL
DEBUT NL
  INSTS
FIN NL                                 {debut();codegen($5);codegen($9);fin();}
;

l_entree : LVAL l_entree               { $$ = creer_noeudEntree($1,$2);}
|                                      {}
;

INSTS : INST                           { $$ = $1; }
| INST INSTS                           { $$ = creer_noeudInst($1,$2); }
;

INST : EXP NL                          { $$ = $1; }
| VAR LVAL NL                          { $$ = creer_noeudDecla($2); }
| LVAL AFFECT EXP NL                   { $$ = creer_noeudAffect($1,$3); }
| VAR LVAL '[' EXP ']' NL              { $$ = creer_noeudTab($2,$4); }
| LVAL '[' EXP ']' AFFECT EXP NL       { $$ = creer_noeudTabaffect($1,$3,$6); }
| AFFICHER EXP NL                      { $$ = creer_noeudSortie($2); }

| TQ EXP FAIRE NL
    INSTS
  FTQ NL                               { $$ = creer_noeudTantque($2,$5);}

| SI EXP ALORS NL
    INSTS
  SINON NL
    INSTS
  FSI NL                               { $$ = creer_noeudCondition($2,$5,$8); }
;

LVAL : ID                              { $$ = creer_feuilleId($1); }

EXP : NB                               { $$ = creer_feuilleNb($1); }
| ID                                   { $$ = creer_feuilleId($1); }
| EXP '+' EXP                          { $$ = creer_noeudOp('+', $1, $3); }
| EXP '-' EXP                          { $$ = creer_noeudOp('-', $1, $3); }
| EXP '*' EXP                          { $$ = creer_noeudOp('*', $1, $3); }
| EXP '/' EXP                          { $$ = creer_noeudOp('/', $1, $3); }
| '(' EXP ')'                          { $$ = $2; }
| LVAL '[' EXP ']'                     { $$ = creer_noeudValTab($1,$3); }
| EXP '=' EXP                          { $$ = creer_noeudComp('=', $1, $3); }
| EXP '<' EXP                          { $$ = creer_noeudComp('<', $1, $3); }
| EXP '>' EXP                          { $$ = creer_noeudComp('>', $1, $3); }
| EXP OU EXP                           { $$ = creer_noeudOu($1, $3); }
| EXP ET EXP                           { $$ = creer_noeudEt($1, $3); }
| NON EXP                              { $$ = creer_noeudNon($2); }
;

%%


int main( int argc, char * argv[] ) {

  extern FILE *yyin;
  if (argc == 1){
    fprintf(stderr, "aucun fichier fournie\n");
    return 1;
  }
  yyin = fopen(argv[1],"r");
  yyparse();
  return 0;
}
