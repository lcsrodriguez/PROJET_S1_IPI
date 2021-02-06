// Dépendances des librairies d
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dépendances des librairies du projet
#include "stack.h"
#include "grid.h"

#define BUFFER_LENGTH 256       // Déclaration de la limite du buffer


/*
 * @requires    buffer déjà initialisé (tableaux de caractères avec la limite BUFFER_LENGTH)
 *              g est une grille valide déjà initialisée
 *              i est un numéro de joueurs valide
 * @assigns     *x et *y
 * @ensures     modifie *x et *y afin qu'ils contiennent la valeur par défaut
 */
void ask_coords(char buffer[], grid g, int *x, int *y, int i){
    int FLAG = 0; // Variable pour garantir la fin de la confirmation par l'utilisateur

    /*
     * ------------------------------------------------
     *         Justification de la terminaison
     * ------------------------------------------------
     *  Cette boucle se termine lorsque le joueur i
     *  décide de confirmer les coordonnées rentrées.
     */
    while (FLAG == 0){
        // Affichage du plateau actuel
        printf("Tour du joueur %d\n", i);
        grid_print(g);

        // Demande de la case à sélectionner
        printf("Quelle case choisissez-vous ?\n");
        fgets(buffer, BUFFER_LENGTH, stdin);
        sscanf(buffer, "%d %d", x, y);
        
        // Affichage de la pile à la case sélectionné
        grid_print_stack(g, *x, *y);

        // Confirmation par l'utilisateur
        char c = '\0';
        printf("Voulez-vous mettre le jeton ici ?\n");
        fgets(buffer, BUFFER_LENGTH, stdin);
        sscanf(buffer, "%c", &c);
        if (strcmp(&c, "o") == 0) FLAG = 1;
    }
}

/*
 * @requires    g est une grille valide déjà initialisée
 *              x et y sont les coordonnées cartésiennes d'une case valide
 * @assigns     nothing
 * @
 */

int test_egalite_jetons_tete(grid g, int x, int y){
    stack s = g.t[x - 1][y - 1]; // Pile à la case (x, y)
    if (!is_empty_stack(s)){ // Test nécessaire pour éviter tout segmentation fault
        if (!is_empty_stack(s->next)){ // Test nécessaire pour éviter tout segmentation fault
            int a = s->v;
            int b = s->next->v;
            return a == b; // On test l'égalité entre les 2 jetons du dessus
        }else{
            return 0;
        }
    }
    return 0;
}


/*
 * @requires    g est une grille valide et déjà initialisée
 *              x et y sont les coordonnées cartésiennes d'une case valide de g
 *              i est un identifiant d'un joueur valide
 * @assigns     g.t, **activated_cases
 * @ensures     modifie la grille g en suivant les règles du jeu
 */
void ExploreCell(grid g, int** activated_cases, int x, int y, int i){
    int n = g.n; // Déclaration de la taille de la grille
    grid_insert(g, x, y, i); // Insertion du jeton
    if (test_egalite_jetons_tete(g, x, y)){ // Si la case est activée
        // La case est alors activée
        activated_cases[x - 1][y - 1] = i; // On actualise son état dans ce tableau 2D

        // On retire les 2 jetons du dessus
        pop(&g.t[x - 1][y - 1]);
        pop(&g.t[x - 1][y - 1]);

        // On insère au N/S/E/O des jetons identiques
        /*
            N : x - 1, y
            S : x + 1, y
            E : x, y + 1
            O : x, y - 1
            int varX[4] = {x - 1, x + 1, x, x};
            int varY[4] = {y, y, y + 1, y - 1};
        */
        // Tableaux des coordonnées des 4 cases du voisinage
        int varX[4] = {x - 1, x, x, x + 1};
        int varY[4] = {y, y + 1, y - 1,  y};

        // Pour chacune de ses cases,
        for (int k = 0; k < 4; k++){
            int dx = varX[k]; // Abscisse de la case du voisinage
            int dy = varY[k]; // Ordonnée de la case du voisinage
            if (1 <= dx && dx <= n && 1<= dy && dy <= n){ // Si la case se trouve bien dans la grille (et pas en dehors)
                //printf("Traitement voisins : (%d, %d) - %d\n", dx, dy, activated_cases[dx - 1][dy - 1]);
                if (activated_cases[dx - 1][dy - 1] != i){ // Si la case n'est pas déjà activée, on peut insérer un jeton
                    //printf("Insertion\n");
                    ExploreCell(g, activated_cases, dx, dy, i); // On appelle une nouvelle fois cette fonction sur la case du voisinage en question
                }
            }
        }
    }else{
        // La case n'est pas activée
        //printf("La case (%d, %d) n'est pas activée\n", x, y);
    }
}
/*
 * @requires    g est une grille valide et déjà initialisée
 *              j est le bon nombre de joueur
 * @assigns     nothing
 * @ensures     retourne le numéro du joueur gagnant la partie
 */
int DeterminationGagnant(grid g, int j){
    // Détermination du gagnant
    int t[j]; // Tableau 1D contenant les scores à actualiser de chacun des joueurs
    int n = g.n; // Taille de la grille

    // Initialisation du tableau t à 0
    for (int k = 0; k < j; k++)
        t[k] = 0;

    // Comptage des scores par double-parcours imbriqués
    for (int k = 0; k < n; k++)
        for (int l = 0; l < n; l++)
            t[g.t[k][l]->v - 1] += 1;

    // Recherche du maximum parmi les scores déjà calculés
    int max = 0;
    for (int k = 1; k < j; k++)
        if (t[max] < t[k])
            max = k;

    // Ajustemenet nécessaire (car différence entre 1..j et les indices du tableaux)
    int gagnant = max + 1;
    return gagnant;
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *           FONCTION PRINCIPALE
 * @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 */
int main(){

    char buffer[BUFFER_LENGTH]; // Déclaration du buffer pour la saisie utilisateur sur l'entrée standard

    int j, n; // Déclaration des variables pour le nbre de joueurs et la taille de la grille

    // Demande nombre de joueurs -> j
    printf("Nombre de joueurs (j) : ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &j);

    // Demande taille du plateau -> n
    printf("Taille du plateau (n) : ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &n);

    // Affichages complémentaires
    printf("##################\n");
    printf("Nombre de joueurs (j) : %d\n", j);
    printf("Taille du plateau (n) : %d\n", n);
    printf("##################\n");

    // Initialisation de la grille
    grid g = grid_init(n);

    // Affichage de la grille initiale
    grid_print(g);

    // Variable contenant le numéro (=couleur du joueur)
    int i = 1; // on commence par le premier joueur

    // Tableau pour stocker les cases activées lors d'un tour
    int **activated_cases = NULL;
    activated_cases = malloc(n*sizeof(int*));
    for (int a = 0; a < n; a++)
        activated_cases[a] = calloc(n, sizeof(int));

    // Initialisation de ce tableau à des valeurs nulles
    for (int a = 0; a < n; a++)
        for (int b = 0; b < n; b++)
            activated_cases[a][b] = 0;

    /*
     * ------------------------------------------------
     *         Justification de la terminaison
     * ------------------------------------------------
     *  Cette boucle se termine lorsque la grille ne
     *  possède plus de cases sans jetons.
     *  Or, à chaque tour de la partie, on ajoute un ou plusieurs
     *  jetons.
     *  A partir d'un certain tour, chaque case de la grille contiendra
     *  au moins 1 jeton.
     *  A ce moment, le programme sort de cette boucle.
     *
     *  Pour plus d'informations, voir le rapport.
     */
    while (!is_grid_complete(g)){     // Tant que la grille n'est pas complète
        int x, y; // Initialisation du curseur
        
        // Demande de saisie par l'utilisateur
        ask_coords(buffer, g, &x, &y, i); 
       
        /* Convention
            Si x et y sont les coordonnées rentrées, cela correspond
            à la case [x - 1][y - 1] dans la grille
        */

        // Traitement de la case
        ExploreCell(g, activated_cases, x, y, i);

        // Traitement de changement de tour
        if (i == j){ // Si on est arrivé au dernier joueur, on revient au premier
            i = 1;
        }else{
            i += 1; // Si on n'est pas le dernier joueur, on incrémente juste de 1
        }
        // A la fin de chaque tour, on réinitialise le tableaux stockant les cases activées lors du tour précédent.
        for (int a = 0; a < n; a++)
            for (int b = 0; b < n; b++)
                activated_cases[a][b] = 0;
    }

    // Gestion de la fin de partie
    printf("GRILLE COMPLETE => FIN\n");
    grid_print(g); // Affichage de la grille à son état final

    // Détermination du gagnant
    printf("\n\nLe joueur gagnant est le joueur n°%d.\n\n\n", DeterminationGagnant(g, j));


    // Etape très importante : libération de la mémoire
    
    // Libération de l'espace mémoire du tas
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // Libération de la pile en (i, j)
            while (!is_empty_stack(g.t[i][j])){
                pop(&g.t[i][j]);
            }
        }
        // Libération de toute la ligne i
        free(g.t[i]);
        free(activated_cases[i]);
    }
    // Libérations finales
    free(g.t);
    free(activated_cases);
    
    // Fin du programme
    return 0;
}