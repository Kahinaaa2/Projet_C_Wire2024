#include "main.h"

int main() {
    AVL* station = NULL;

    // Lecture et insertion des données
    lire_donnees_en_bloc(&station);

    // Affichage des résultats
    affiche(station);

    // Libération de la mémoire
    libererAVL(station);

    return 0;
}
