#ifndef _STACK_H
#define _STACK_H


/*
###################################################################
    Déclaration des types abstraits et concrets
###################################################################
*/

// Déclaration du type jeton (= élément d'une pile)
typedef int jeton;

/*  
    Déclaration du maillon contenant la valeur du jeton, 
    puis un pointeur vers le maillon suivant
*/
struct stack_base{
    jeton v;
    struct stack_base *next;
};


// Déclaration du type stack (= pile)
typedef struct stack_base *stack;

/*
###################################################################
    Déclaration des fonctions (prototypes)
###################################################################
*/

/*
    @requires   nothing
    @assigns    nothing
    @ensures    retourne une pile vide
*/
stack empty_stack();

/*
    @requires   s est une pile valide
    @assigns    nothing
    @ensures    retoure 1 si la pile est vide, 0 sinon
*/
int is_empty_stack(stack s);

/*
    @requires   s est l'adresse d'une pile valide
    @assigns    nothing
    @ensures    retourne la pile s avec le jeton j en plus
*/
stack cons(jeton j, stack s);

/*
    @requires   j est un jeton valide
                *s est une pile valide
    @assigns    *s
    @ensures    ajoute le jeton j à la pile *s
*/
void push(jeton j, stack *s);

/*
    @requires   *s est une pile valide
    @assigns    *s
    @ensures    retourne le jeton j en tête de pile
*/
void pop(stack *s);

/*
    @requires   s est l'adresse d'une pile valide
    @assigns    nothing
    @ensures    affiche en ligne le contenu de la pile s
*/
void print_stack(stack s);

/*
    @requires   s est l'adresse d'une pile valide
    @assigns    nothing
    @ensures    affiche le jeton en tête de la pile s
*/
void stack_head(stack s);

#endif