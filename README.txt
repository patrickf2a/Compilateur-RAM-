# FERNANDES DE FARIA PATRICK
# ALI-HADEF JAMEL


############## UTILISATION DU PROGRAMME ################

- Le programme est un compilateur qui traduit un algorithme en langage algorithmique vers la langage de la machine RAM.

- Pour cela il suffit d'exécuter le programme arc avec en argument un fichier contenant un algorithme. La sortie sera dans un fichier a.out comme demandé qui pourra être tester sur le simulateur de la machine RAM de Monsieur Zanotti lien : http://zanotti.univ-tln.fr/RAM/ram.php

Exemple d'execution: make -B puis une fois compiler tapé ./arc exemple.algo .


############# CONTENUE DE L'ARCHIVE #######################

- lexer.lex: Analyseur lexicale avec l'outil Flex, il décompose le flux de données en entrée en unités lexicales. (opérateurs, DEBUT, FIN,etc..).

- parser.y: Analyseur syntaxique avec l'outil Bison, il permet de créer une représentation du flots d’unités lexicales reflétant la structure grammaticale avec notamment:
La définition de l'axiome: pour notre part ici c'est "%start PROG"

La définition des terminaux et non-terminaux.

La définition des priorités et de l'associativité :

Par exemple les opérateurs +, -, *, /, % sont associatifs à gauche donc ils sont précédés par %left. Les opérateurs *, /, % sont prioritaires sur les autres opérateurs donc on les place après en dessous.

- ts.h/.c: Gestion de la liste chainée qui permettra de mémoriser et gérer les identificateurs.

- asa.h: Contient la structure asa permettant de créé un arbre abstrait de notre algorithme.
Chaque noeud de notre arbre est composé de son type puis de sa structure propre.
Par exemple: un noeud pour une opération arithmétique sera composé de l'opérateur puis de deux pointeurs.

- asa.c: Contient les fonctions creer_<type> qui permettent de construire un noeud de l'arbre abstrait du type correspondant, il contient également la fonction codegen qui produit le code pour la machine RAM à partir de l'arbre abstrait et de la table de symboles.


############# CAPACITE DU COMPILATEUR #########################

* Au niveau de l'algorithme :
- L'algorithme doit commencer par ALGO (nom de l'algo) et ensuite ENTREE (suivi de variable utilisés) .
- Ensuite par DEBUT et finir par FIN.
- Chaque instruction doit être séparé par un saut de ligne.
- L’affectation se fait avec le symbole <-
- Les espaces et tabulations sont ignorés.
- Les variables doivent être déclarées une par une précédés par le mot VAR (ex: VAR nomvariable).
- Les structures doivent être de la forme suivante : SI-ALORS-SINON-FSI pour la structure SI-SINON, ou TQ-FAIRE-FTQ pour la structure TANT QUE.
- Les commentaires doivent commencer par # sur un seule ligne.

* Au niveau du compilateur :
- Les opérations arithmétiques (+, -, *, /, %)
- Les opérations de comparaison (>, <, >=, <=, =, !=)
- Les opérateurs booléens (ET, OU, NON)
- La gestion des parenthèses
- Structures SI-ALORS-SINON-FSI, TQ-FAIRE-FTQ
- Gestion des tableaux. Lors de la declaration seul un entier est possible et non une variable (Exemple: VAR x[3]).
- Gestion des commentaires.
- Entrées/sorties
- L'affectation (exemple: x[0] <- 5)


########### EXEMPLE D'ALGORITHME ##############

Gestion des variables :

ALGO :
ALGO test
ENTREE z
DEBUT
  VAR x
  x <- 5
FIN

Code RAM :
READ
STORE 1
LOAD #5
STORE 2
STOP

Déclaration pendant l'initialisation et gestion des tableaux :

ALGO :
ALGO testtab
ENTREE z
DEBUT
  VAR x[3]
  x[0] <- 5
  x[1] <- 2
  x[2] <- 8
  AFFICHER  x[1]
FIN

CODE RAM :
READ
STORE 1
LOAD #5
STORE 2
LOAD #2
STORE 3
LOAD #8
STORE 4
LOAD 3
STORE 65
LOAD #1
WRITE
STOP

Structure SI-SINON :

ALGO :
ALGO TestSi
ENTREE z
DEBUT
  SI z = 0 ALORS
    AFFICHER 1
  SINON
    AFFICHER 2
  FSI
FIN

CODE RAM :
READ
STORE 1
LOAD #0
STORE 65
LOAD 1
SUB 65
JUMZ 9
LOAD #0
JUMP 10
LOAD #1
JUMZ 14
LOAD #1
WRITE
JUMP 16
LOAD #2
WRITE
STOP

Structure TQ-FAIRE-FTQ :

ALGO:
ALGO TestTq
ENTREE z
DEBUT
  VAR x
  x <- 5
  TQ x > 1 FAIRE
    AFFICHER z
    x <- x-1
  FTQ
FIN

CODE RAM :
READ
STORE 1
LOAD #5
STORE 2
LOAD #1
STORE 65
LOAD 2
SUB 65
JUMG 11
LOAD #0
JUMP 12
LOAD #1
JUMZ 21
LOAD 1
WRITE
LOAD #1
STORE 65
LOAD 2
SUB 65
STORE 2
JUMP 3
STOP
