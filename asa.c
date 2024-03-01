// ALI-HADEF Jamel / FERNANDES Patrick
//
// TP 8 : Compilateur Algo - RAM
//
// asa.c

#include "asa.h"


asa * creer_feuilleNb(int val)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeNb;
  p->nb.val = val;
  p->ninst =1;
  return p;
}

asa * creer_noeudInst( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeInst;
  p->inst.noeud[0]=p1;
  p->inst.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst;

  return p;
}

// OPERATEURS ARITHMETIQUE //
asa * creer_noeudOp( int ope, asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeOp;
  p->op.ope = ope;
  p->op.noeud[0]=p1;
  p->op.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+2;

  return p;
}

// OPERATEURS BOOLEEN //
asa * creer_noeudOu( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeOu;
  p->ou.noeud[0]=p1;
  p->ou.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+5;

  return p;
}

asa * creer_noeudEt( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeEt;
  p->et.noeud[0]=p1;
  p->et.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+5;

  return p;
}

asa * creer_noeudNon( asa * p1 )
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeNon;
  p->non.noeud[0]=p1;
  p->ninst = p1->ninst+3;

  return p;
}
// OPERATEURS DE COMPARAISON //
asa * creer_noeudComp( int ope, asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeComp;
  p->comp.ope = ope;
  p->comp.noeud[0]=p1;
  p->comp.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst+5;

  return p;
}

// BOUCLE / CONDITION //
asa * creer_noeudTantque( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeTantque;
  p->tantque.noeud[0]=p1;
  p->tantque.noeud[1]=p2;
  p->ninst = p->tantque.noeud[0]->ninst + p->tantque.noeud[1]->ninst + 2;

  return p;
}

asa * creer_noeudCondition( asa * p1, asa * p2, asa * p3)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeCondition;
  p->condition.noeud[0]=p1;
  p->condition.noeud[1]=p2;
  p->condition.noeud[2]=p3;
  p->ninst = p1->ninst + p2->ninst + p3->ninst;

  return p;
}

// VARIABLE //
asa * creer_feuilleId(char * nom)
{
  asa *p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeId;
  strcpy(p->id.nom,nom);
  p->ninst =1;
  return p;
}

asa * creer_noeudDecla(asa * p1)
{
  ts_ajouter_id(p1->id.nom, 1);

  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeDecla;
  p->decla.noeud[0]=p1;
  p->ninst = 0;

  return p;
}

asa * creer_noeudAffect( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeAffect;
  p->affect.noeud[0]=p1;
  p->affect.noeud[1]=p2;
  p->ninst = p2->ninst + 1;

  return p;
}

// ENTREE / SORTIE //
asa * creer_noeudEntree( asa * p1, asa * p2 )
{
  asa * p;
  ts_ajouter_id(p1->id.nom, 1);
  //if (p2 != 0 ) ts_ajouter_id(p2->id.nom, 1);

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeEntree;
  p->entree.noeud[0]=p1;
  p->entree.noeud[1]=p2;
  p->ninst = 2;

  return p;
}

asa * creer_noeudSortie( asa * p1)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeSortie;
  p->sortie.noeud[0]=p1;
  p->ninst = 2;

  return p;
}

// GESTION TABLEAU //
asa * creer_noeudTab( asa * p1, asa * p2)
{
  //ts *pts;
  switch(p2->type){
    case typeNb :
      ts_ajouter_id(p1->id.nom, p2->nb.val);
      break;
    case typeId :
      fprintf(stderr,"Impossible de creer un tableau avec une varaiable"); //yyerror
      exit(1);
      break;
    default :
      break;
  }
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeTab;
  p->tab.noeud[0]=p1;
  p->tab.noeud[1]=p2;
  p->ninst = 0;

  return p;
}

asa * creer_noeudTabaffect( asa * p1, asa * p2, asa * p3)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeTabaffect;
  p->tabaffect.noeud[0]=p1;
  p->tabaffect.noeud[1]=p2;
  p->tabaffect.noeud[2]=p3;
  p->ninst = 2;//p2->ninst + p3->ninst + 5;

  return p;
}

asa * creer_noeudValTab( asa * p1, asa * p2)
{
  asa * p;

  if ((p = malloc(sizeof(asa))) == NULL)
    yyerror("echec allocation mémoire");

  p->type = typeValTab;
  p->inst.noeud[0]=p1;
  p->inst.noeud[1]=p2;
  p->ninst = p1->ninst+p2->ninst;

  return p;
}

// LIBERATION MEMOIRE //
void free_asa(asa *p)
{

  if (!p) return;
  switch (p->type) {
  case typeOp :
  case typeInst :
  case typeEntree :
  case typeSortie :
  case typeDecla :
  case typeTab :
    free_asa(p->decla.noeud[0]);
    break;
  case typeTabaffect :
    free_asa(p->tabaffect.noeud[0]);
    free_asa(p->tabaffect.noeud[1]);
    free_asa(p->tabaffect.noeud[2]);
    break;
  default: break;
  }
  free(p);
}

static int pile = 65;
static int ligneno = -1;
FILE* fichier;
//fichier = fopen("a.out", "w+");


void codegen(asa *p)
{
  ts *pts;
  int ret;
  int pos = 0;
  //fichier = fopen("a.out", "w");
  if (!p) return;
  switch(p->type) {

  case typeNb :
    fprintf(fichier,"LOAD #%d\n",p->nb.val);
    ligneno++;
    break;

  case typeId :
    if ( (pts = ts_retrouver_id(p->id.nom)) == 0){
      fprintf(stderr,"variable %s introuvable", p->id.nom); //yyerror
      exit(1);
    }
    fprintf(fichier,"LOAD %d\n",pts->adr);
    ligneno++;
    break;

  case typeInst :
    codegen(p->inst.noeud[0]);
    codegen(p->inst.noeud[1]);
    break;

  case typeDecla :
    break;
  case typeAffect :
    codegen(p->affect.noeud[1]);
    if ( (pts = ts_retrouver_id(p->affect.noeud[0]->id.nom)) == 0){
      fprintf(stderr,"variable %s introuvable", p->affect.noeud[0]->id.nom); //yyerror
      exit(1);
    }
    fprintf(fichier,"STORE %d\n",pts->adr);
    ligneno++;
    break;

  case typeOp :
    codegen(p->op.noeud[1]);
    if (pile <= PILE_MAX){
      fprintf(fichier,"STORE %d\n",pile++);
      ligneno++;
    }
    else {
      yyerror("Impossible d'allouer la memoire sur la pile\n");
      exit(1);
    }
    codegen(p->op.noeud[0]);
    switch (p->op.ope) {
      case '+' :
        fprintf(fichier,"ADD %d\n",--pile);
        ligneno++;
        break;
      case '-' :
        fprintf(fichier,"SUB %d\n",--pile);
        ligneno++;
        break;
      case '*' :
        fprintf(fichier,"MUL %d\n",--pile);
        ligneno++;
        break;
      case '/' :
        fprintf(fichier,"DIV %d\n",--pile);
        ligneno++;
        break;
      default :
        break;
    }
    break;
  case typeTab :
    break;
  case typeTabaffect :
    switch(p->tabaffect.noeud[1]->type){
      case typeNb :
        pos = p->tabaffect.noeud[1]->nb.val;
        break;
      default :
        break;
    }
    if ( (pts = ts_retrouver_id(p->tabaffect.noeud[0]->id.nom)) == 0){
      fprintf(stderr,"variable %s introuvable", p->tabaffect.noeud[0]->id.nom); //yyerror
      exit(1);
    }
    switch(p->tabaffect.noeud[2]->type){
      case typeNb :
        if (pos >= pts->size ){
          fprintf(stderr,"index de liste hors de portée\n"); //yyerror
          exit(1);
        }
        fprintf(fichier,"LOAD #%d\n",p->tabaffect.noeud[2]->nb.val);
        ligneno++;
        fprintf(fichier,"STORE %d\n",pts->adr+pos);
        ligneno++;
        break;
      default :
        break;
    }
    break;

  case typeEntree :
    fprintf(fichier,"READ\n");
    ligneno++;
    if ( (pts = ts_retrouver_id(p->entree.noeud[0]->id.nom)) == 0){
      fprintf(stderr,"variable %s introuvable", p->entree.noeud[0]->id.nom); //yyerror
      exit(1);
    }
    fprintf(fichier,"STORE %d\n",pts->adr);
    ligneno++;
    if (p->entree.noeud[1] != 0) codegen(p->entree.noeud[1]);
    break;

  case typeSortie :
      codegen(p->sortie.noeud[0]);
      fprintf(fichier,"WRITE\n");
      ligneno++;
    break;

  case typeValTab :
    if ( (pts = ts_retrouver_id(p->valtab.noeud[0]->id.nom)) == 0){
      fprintf(stderr,"variable %s introuvable", p->affect.noeud[0]->id.nom); //yyerror
      exit(1);
    }
    switch(p->valtab.noeud[1]->type){
      case typeNb :
        fprintf(fichier,"LOAD %d\n",pts->adr+p->valtab.noeud[1]->nb.val);
        ligneno++;
        break;
      default :
        fprintf(stderr,"Seulement entier pour parcourir tableau [int]");
        break;
    }

  case typeComp :
    codegen(p->comp.noeud[1]);
    if (pile <= PILE_MAX){
      fprintf(fichier,"STORE %d\n",pile++);
      ligneno++;
    }
    else {
      yyerror("Impossible d'allouer la memoire sur la pile\n");
      exit(1);
    }
    codegen(p->comp.noeud[0]);
    switch (p->comp.ope) {
      case '=' :
        fprintf(fichier,"SUB %d\n",--pile);
        ligneno++;
        fprintf(fichier,"JUMZ %d\n",ligneno+4);
        ligneno++;
        fprintf(fichier,"LOAD #0\n");
        ligneno++;
        fprintf(fichier,"JUMP %d\n",ligneno+3);
        ligneno++;
        fprintf(fichier,"LOAD #1\n");
        ligneno++;
        break;
      case '<' :
        fprintf(fichier,"SUB %d\n",--pile);
        ligneno++;
        fprintf(fichier,"JUML %d\n",ligneno+4);
        ligneno++;
        fprintf(fichier,"LOAD #0\n");
        ligneno++;
        fprintf(fichier,"JUMP %d\n",ligneno+3);
        ligneno++;
        fprintf(fichier,"LOAD #1\n");
        ligneno++;
        break;
      case '>' :
        fprintf(fichier,"SUB %d\n",--pile);
        ligneno++;
        fprintf(fichier,"JUMG %d\n",ligneno+4);
        ligneno++;
        fprintf(fichier,"LOAD #0\n");
        ligneno++;
        fprintf(fichier,"JUMP %d\n",ligneno+3);
        ligneno++;
        fprintf(fichier,"LOAD #1\n");
        ligneno++;
        break;
      default :
        break;
    }
    break;
  case typeTantque :
    ret = ligneno;
    codegen(p->tantque.noeud[0]);
    fprintf(fichier,"JUMZ %d\n", ligneno+p->tantque.noeud[1]->ninst+3);
    ligneno++;
    codegen(p->tantque.noeud[1]);
    fprintf(fichier,"JUMP %d\n", ret);
    ligneno++;
    break;

  case typeCondition :
    codegen(p->condition.noeud[0]);
    fprintf(fichier,"JUMZ %d\n", ligneno+p->condition.noeud[1]->ninst+3);
    ligneno++;
    codegen(p->condition.noeud[1]);
    fprintf(fichier,"JUMP %d\n", ligneno+p->condition.noeud[2]->ninst+2);
    ligneno++;
    codegen(p->condition.noeud[2]);
    break;
  case typeNon :
    codegen(p->non.noeud[0]);
    fprintf(fichier,"JUMZ %d\n",ligneno+4);
    ligneno++;
    fprintf(fichier,"LOAD #0\n");
    ligneno++;
    fprintf(fichier,"JUMP %d\n",ligneno+3);
    ligneno++;
    fprintf(fichier,"LOAD #1\n");
    ligneno++;
    break;
  case typeOu :
    codegen(p->ou.noeud[0]);
    fprintf(fichier,"JUMZ %d\n",ligneno+3);
    ligneno++;
    fprintf(fichier,"JUMP %d\n",ligneno+4);
    ligneno++;
    codegen(p->ou.noeud[1]);
    fprintf(fichier,"JUMZ %d\n",ligneno+4);
    ligneno++;
    fprintf(fichier,"LOAD #1\n");
    ligneno++;
    fprintf(fichier,"JUMP %d\n",ligneno+3);
    ligneno++;
    fprintf(fichier,"LOAD #0\n");
    ligneno++;
    break;
  case typeEt :
    codegen(p->et.noeud[0]);
    fprintf(fichier,"JUMZ %d\n",ligneno+6);
    ligneno++;
    codegen(p->ou.noeud[1]);
    fprintf(fichier,"JUMZ %d\n",ligneno+4);
    ligneno++;
    fprintf(fichier,"LOAD #1\n");
    ligneno++;
    fprintf(fichier,"JUMP %d\n",ligneno+3);
    ligneno++;
    fprintf(fichier,"LOAD #0\n");
    ligneno++;
    break;
  default :
    break;
  }
}
void debut(){
  fichier = fopen("a.out", "w");
}

void test(){
  //fichier = fopen("a.out", "w");
  fprintf(fichier, "test reussi");
}

void fin(){
  fprintf(fichier,"STOP\n");
  ligneno++;
  fclose(fichier);
}

void yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  exit(0);
}
