// ALI-HADEF Jamel / FERNANDES Patrick
//
// TP 8 : Compilateur Algo - RAM
//
// asa.h

#ifndef ASA_H
#define ASA_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ts.h"

//| LIRE LVAL                       { $$ = creer_noeudEntree($2); }
typedef enum {typeNb, typeId, typeOp, typeInst, typeDecla, typeAffect, typeTab, typeTabaffect, typeEntree, typeSortie, typeValTab, typeComp, typeOu, typeEt, typeNon, typeTantque, typeCondition} typeNoeud;

typedef struct {
  int val;
} feuilleNb;

typedef struct {
  char nom[64];
} feuilleId;

typedef struct {
  int ope;
  struct asa * noeud[2];
} noeudOp;

typedef struct {
  struct asa * noeud[2];
} noeudInst;

typedef struct {
  struct asa * noeud[1];
} noeudDecla;

typedef struct {
  struct asa * noeud[2];
} noeudAffect;

typedef struct {
  struct asa * noeud[2];
} noeudTab;

typedef struct {
  struct asa * noeud[3];
} noeudTabaffect;

typedef struct {
  struct asa * noeud[2];
} noeudEntree;

typedef struct {
  struct asa * noeud[1];
} noeudSortie;

typedef struct {
  struct asa * noeud[2];
} noeudValTab;

typedef struct {
  int ope;
  struct asa * noeud[2];
} noeudComp;

typedef struct {
  struct asa * noeud[2];
} noeudOu;

typedef struct {
  struct asa * noeud[2];
} noeudEt;

typedef struct {
  struct asa * noeud[1];
} noeudNon;

typedef struct {
  struct asa * noeud[2];
} noeudTantque;

typedef struct {
  struct asa * noeud[3];
} noeudCondition;

typedef struct asa{
  typeNoeud type;
  int ninst;

  union {
    feuilleNb nb;
    feuilleId id;
    noeudOp op;
    noeudInst inst;
    noeudDecla decla;
    noeudAffect affect;
    noeudTab tab;
    noeudTabaffect tabaffect;
    noeudEntree entree;
    noeudSortie sortie;
    noeudValTab valtab;

    noeudComp comp;
    noeudOu ou;
    noeudEt et;
    noeudNon non;
    noeudTantque tantque;
    noeudCondition condition;
  };
} asa;


// fonction d'erreur utilisée également par Bison
void yyerror(const char * s);

/*
  Les fonctions creer_<type> construise un noeud de l'arbre
  abstrait du type correspondant et renvoie un pointeur celui-ci
 */
asa * creer_feuilleNb( int value );
asa * creer_feuilleId( char * nom );
asa * creer_noeudOp( int ope, asa * p1, asa * p2 );
asa * creer_noeudInst( asa * p1, asa * p2 );
asa * creer_noeudDecla( asa * p1 );
asa * creer_noeudAffect( asa * p1, asa * p2 );
asa * creer_noeudTabaffect( asa * p1, asa * p2, asa * p3 );
asa * creer_noeudTab( asa * p1, asa * p2 );
asa * creer_noeudEntree( asa * p1 , asa * p2 );
asa * creer_noeudSortie( asa * p1 );
asa * creer_noeudValTab( asa * p1 , asa * p2 );

asa * creer_noeudComp( int ope, asa * p1, asa * p2 );
asa * creer_noeudOu( asa * p1, asa * p2 );
asa * creer_noeudEt( asa * p1, asa * p2 );
asa * creer_noeudNon( asa * p1);
asa * creer_noeudTantque( asa * p1, asa * p2 );
asa * creer_noeudCondition( asa * p1, asa * p2 , asa * p3 );
void fin();
void debut();
void test();

void free_asa(asa *p);

// produit du code pour la machine RAM à partir de l'arbre abstrait
// ET de la table de symbole
void codegen(asa *p);

extern ts * tsymb;

#endif
