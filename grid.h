#ifndef _GRID_H
#define _GRID_H

#include "stack.h"

/*
###################################################################
    Déclaration des types abstraits et concrets
###################################################################
*/

// Définition du type struct matrix
struct matrix{
    stack **t;      // Matrice de piles
    int n;          // Taille de la matrice
};
// Renommage en type grid
typedef struct matrix grid;


/*
###################################################################
    Déclaration des fonctions (prototypes)
###################################################################
*/


/*
    @requires   n est un entier naturel non nul
    @assigns    g
    @ensures    modifie la grille **t en la remplissant de piles vides
*/
grid grid_init(int n);

/*
    @requires   g est une grille valide déjà initialisée
    @assigns    nothing
    @ensures    affiche le plateau (dans le format demandé)
*/
void grid_print(grid g);

/*
    @requires   x et y entre 0 et n - 1
    @assigns    nothing
    @ensures    affiche la pile de la case (x,y)
*/
void grid_print_stack(grid g, int x, int y);

/*
    @requires   x et y entre 0 et n - 1, k entre 1 et j
    @assigns    g.t
    @ensures    insère à la coordonnée (x, y) le jeton k
*/
void grid_insert(grid g, int x, int y, int k);

/*
    @requires   g est une grille valide
    @assigns    nothing
    @ensures    retourne 1 si la grille est complète, 0 sinon
*/
int is_grid_complete(grid g);

#endif