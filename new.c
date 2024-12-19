#include <stdio.h>
#include <stdlib.h>

// Structure de l'AVL
typedef struct AVL {
    long identifiant;
    long consommation;
    long capacite;
    int eq;  // Facteur d'équilibre
    struct AVL* fg;
    struct AVL* fd;
} AVL;

// Fonction pour calculer le minimum entre deux valeurs
long min(long a, long b) {
    return a < b ? a : b;
}

// Fonction pour calculer le maximum entre deux valeurs
long max(long a, long b) {
    return a > b ? a : b;
}

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

int main() {
    long v1, v2, v3;
    AVL* station = NULL;
    int h = 0;

    while (scanf("%ld;%ld;%ld\n", &v1, &v2, &v3) == 3) {
        if (v1 < 0 || v2 < 0 || v3 < 0) {
            printf("Données incorrectes\n");
            exit(7);
        }
        station = insererAVL(station, v1, v2, v3, &h);
    }

    affiche(station);
    libererAVL(station);

    return 0;
}
