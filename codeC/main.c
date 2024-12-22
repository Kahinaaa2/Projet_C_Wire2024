#include "main.h"


// Lecture des données en bloc pour optimisation
void lireDonnees(AVL** station) {
    char recup[1024];
    int h = 0;
    long v1, v2, v3;

    while (fgets(recup, 1024, stdin) != NULL) {
        if (sscanf(recup, "%ld;%ld;%ld", &v1, &v2, &v3) == 3) {
            if (v1 < 0 || v2 < 0 || v3 < 0) {
                printf("Les données du fichiers sont incorrectes et ne correspondent pas\n");
                exit(7);
            }
            *station = insererAVL(*station, v1, v2, v3, &h);
        }
    }
}

int main() {
    AVL* station = NULL;

    // Lecture et insertion des données
    lireDonnees(&station);

    // Affichage des résultats
    affiche(station);

    // Libération de la mémoire
    libererAVL(station);

    return 0;
}
