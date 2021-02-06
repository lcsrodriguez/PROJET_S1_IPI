#include "stack.h"
#include "grid.h"
#include <stdlib.h>
#include <stdio.h>

/*
###################################################################
    Implémentation des fonctions
###################################################################
*/

grid grid_init(int n){
    grid g;             // Défintion de l'objet grille
    g.n = n;            // Défintion de la taille de la grille

    // Allocation dynamique pour lignes
    g.t = malloc(n*sizeof(stack*));

    // Allocation dynamique des colonnes
    for (int i = 0; i < n; i++)
        g.t[i] = calloc(n, sizeof(stack)); // Allocation de cases contigües pour choix de cohérence

    // Création des piles vides pour chacune des cases
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g.t[i][j] = empty_stack();
    return g;
}

void grid_print(grid g){
    int n = g.n; // Définition de la taille de la grille (nxn)

    // Affichages secondaires
    printf("    | ");
    // Affichage du numéro de la colonne
    for (int i = 1; i <= n; i++)
        printf("%3d", i);

    printf("\n");
    printf("----+-----------------\n");

    // Affichage principal de la grille par double parcours imbriqués
    for(int i = 0; i < n; i++){
        printf("%3d | ",  i + 1); // Affichage du numéro de la ligne
        for(int j = 0; j < n; j++){
            if (!is_empty_stack(g.t[i][j])){ 
                /*
                    Très important pour éviter les segmentation faults
                    (sinon la pile est NULL et tente d'accèder à NULL->next)
                    Sans cette condition, la fonction tente d'accèder à une zone de la mémoire interdite
                */
                printf("%3d", (g.t[i][j])->v); // On affiche le jeton en tête de la pile
            }else{
                printf("   "); // Lorsque la pile est vide, il n'y a donc aucun jeton sur la case, on affiche rien
            }
        }
        printf("\n");
    } 
}

/*
 * AVERTISSEMENT
 * Pour la manipulation des piles (push, pop, afficher) qui se trouvent à chaque case de la grille,
 * Il faut prendre en compte le fait que si l'utilisateur souhaite opérer sur la case (i, j),
 * nous devons en réalité opérer sur la case du tableau (x - 1, y - 1), du fait du décalage des indices entre l'énoncé et
 * l'implémentation des tableaux en C.
 */

void grid_print_stack(grid g, int x, int y){
    print_stack(g.t[x - 1][y - 1]);
}

void grid_insert(grid g, int x, int y, int k){
    push(k, &g.t[x - 1][y - 1]);
}

/*
 * Cette fonction est très utile pour nous car c'est elle qui nous permet de savoir si la partie est terminée ou non
 */
int is_grid_complete(grid g){
    int n = g.n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (is_empty_stack(g.t[i][j]))
                return 0;
    return 1;
}