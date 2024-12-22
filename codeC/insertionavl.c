#include "insertionavl.h"

// Création d'un nouveau noeud d'AVL
AVL* creerAVL(long nb, long cap, long conso) {
    AVL* nouveau = malloc(sizeof(AVL));
    if (nouveau == NULL) {
        printf("erreur d'allocation\n");
        exit(1);
    }
    nouveau->identifiant = nb;
    nouveau->capacite = cap;
    nouveau->consommation = conso;
    nouveau->eq = 0;
    nouveau->fg = NULL;
    nouveau->fd = NULL;
    return nouveau;
}

// Fonction d'insertion dans un AVL
AVL* insererAVL(AVL* a, long e, long v, long c, int* h) {
    if (a == NULL) {
        *h = 1;
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
        *h = 0;
    }

    if (*h != 0) {
        a->eq += *h;
        a = equilibreAVL(a);
        *h = (a->eq == 0) ? 0 : 1;
    }

    return a;
}
