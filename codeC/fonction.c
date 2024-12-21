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

// Lecture des données en bloc pour optimisation
void lire_donnees_en_bloc(AVL** station) {
    char buffer[BUFFER_SIZE];
    int h = 0;
    long v1, v2, v3;

    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        if (sscanf(buffer, "%ld;%ld;%ld", &v1, &v2, &v3) == 3) {
            if (v1 < 0 || v2 < 0 || v3 < 0) {
                fprintf(stderr, "Erreur : Données incorrectes\n");
                exit(7);
            }
            *station = insererAVL(*station, v1, v2, v3, &h);
        }
    }
}
