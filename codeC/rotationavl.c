#include "rotationavl.h"

// Rotation droite
AVL* rotationDroite(AVL* a) {
    AVL* pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;

    a->eq = a->eq - min(pivot->eq, 0) + 1;
    pivot->eq = max(max(a->eq + 2, a->eq + pivot->eq + 2), pivot->eq + 1);

    return pivot;
}

// Rotation gauche
AVL* rotationGauche(AVL* a) {
    AVL* pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;

    a->eq = a->eq - max(pivot->eq, 0) - 1;
    pivot->eq = min(min(a->eq - 2, a->eq + pivot->eq - 2), pivot->eq - 1);

    return pivot;
}

// Double rotation droite
AVL* doubleRotationDroite(AVL* a) {
    a->fg = rotationDroite(a->fg);
    return rotationGauche(a);
}

// Double rotation gauche
AVL* doubleRotationGauche(AVL* a) {
    a->fd = rotationGauche(a->fd);
    return rotationDroite(a);
}

// Fonction pour équilibrer l'AVL
AVL* equilibreAVL(AVL* a) {
    if (a->eq <= -2) { // Sous-arbre gauche déséquilibré
        if (a->fg->eq <= 0) {
            return rotationDroite(a);
        } else {
            return doubleRotationDroite(a);
        }
    } else if (a->eq >= 2) { // Sous-arbre droit déséquilibré
        if (a->fd->eq >= 0) {
            return rotationGauche(a);
        } else {
            return doubleRotationGauche(a);
        }
    }
    return a;
}
