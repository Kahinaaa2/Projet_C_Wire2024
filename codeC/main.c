#include "main.h"


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
