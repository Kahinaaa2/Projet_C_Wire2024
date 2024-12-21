#include "insertionavl.h"

// Création d'un nouveau noeud d'AVL
AVL* creerAVL(long nb, long cap, long conso) {
    AVL* new = malloc(sizeof(AVL));
    if (new == NULL) {
        printf("Allocation échouée\n");
        exit(1);
    }
    new->identifiant = nb;
    new->capacite = cap;
    new->consommation = conso;
    new->eq = 0;
    new->fg = NULL;
    new->fd = NULL;
    return new;
}

// Fonction d'insertion dans un AVL
AVL* insererAVL(AVL* a, long e, long v, long c, int* h) {
    if (a == NULL) {
        *h = 0;
        return creerAVL(e, v, c);
    }
    
    if (e < a->identifiant) {
        a->fg = insererAVL(a->fg, e, v, c, h);
        *h = -(*h);
    } else if (e > a->identifiant) {
        a->fd = insererAVL(a->fd, e, v, c, h);
    } else { // Mise à jour si l'identifiant existe déjà
        a->consommation += c;
        a->capacite += v;
    }

    if (*h != 0) {
        a->eq += *h;
        a = equilibreAVL(a);
        *h = (a->eq == 0) ? 0 : 1;
    }

    return a;
}
