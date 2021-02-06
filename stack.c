#include "stack.h"

#include <stdlib.h>
#include <stdio.h>


/*
###################################################################
    Implémentation des fonctions
###################################################################
*/

stack empty_stack(){
    return NULL; // retourne une pile vide
}

int is_empty_stack(stack s){
    return (s == NULL);
}

stack cons(jeton j, stack s){
    // Construction du maillon pour le jeton j et placement de ce dernier au début de la liste chaînée.
    stack res;
    res = malloc(sizeof(struct stack_base)); // Allocation d'un nouveau maillon à la liste chaînée.
    res->v = j;
    res->next = s;
    return res;
}

void push(jeton j, stack *s){
    *s = cons(j, *s);
}

void pop(stack *s){
    int res;
    stack tmp;      // Pour garder l'adresse du maillon que je vais libérer après
    res = (*s)->v;
    tmp = *s;
    *s = (*s)->next;
    free(tmp);
}

void print_stack(stack s){
    printf("Contenu de la pile \n");
    while (!is_empty_stack(s)){
        printf("[%d]\n", s->v);
        s = s->next;
    }
    printf("\n");
}

void stack_head(stack s){
    printf("Affichage de la tête de pile\n");
    printf("%d", s->v);
}