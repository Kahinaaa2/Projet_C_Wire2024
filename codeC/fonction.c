#include "fonction.h"

// Fonction pour calculer le minimum entre deux valeurs
long min(long a, long b) {
    return a < b ? a : b;
}

// Fonction pour calculer le maximum entre deux valeurs
long max(long a, long b) {
    return a > b ? a : b;
}

// Fonction pour afficher les données de chaque noeud de l'AVL
void affiche(AVL* a) {
    if (a != NULL) {
        affiche(a->fg);
        printf("%ld:%ld:%ld\n", a->identifiant, a->capacite, a->consommation);
        affiche(a->fd);
    }
}

// Fonction pour libérer la mémoire allouée
void libererAVL(AVL* a) {
    if (a != NULL) {
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a);
    }
}
