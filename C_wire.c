#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure pour un nœud AVL
typedef struct AVLNode {
    char id_station[20];   // Identifiant de la station
    char type[5];          // Type de la station : "HV-B", "HV-A", "LV"
    int capacite;          // Capacité de la station
    int consommation;      // Somme des consommations
    int hauteur;           // Hauteur du nœud pour l'équilibre AVL
    struct AVLNode* gauche; // Pointeur vers le sous-arbre gauche
    struct AVLNode* droit;  // Pointeur vers le sous-arbre droit
} AVLNode;

// Obtenir la hauteur d'un nœud
int obtenirHauteur(AVLNode* noeud) {
    if (noeud == NULL) {
        return 0;
    } else {
        return noeud->hauteur;
    }
}


// Calculer le facteur d'équilibre
int calculerFacteurEquilibre(AVLNode* noeud) {
    if (noeud == NULL) {
        return 0;
    }
    return obtenirHauteur(noeud->gauche) - obtenirHauteur(noeud->droit);
}

// Fonction pour insérer un nœud dans l'arbre AVL
AVLNode* inserer(AVLNode* racine, const char* id, const char* type, int capacite, int consommation) {
    if (racine == NULL) {
        // Si l'arbre est vide, créer un nouveau nœud
        AVLNode* nouveau = (AVLNode*)malloc(sizeof(AVLNode));
        strcpy(nouveau->id_station, id);
        strcpy(nouveau->type, type);
        nouveau->capacite = capacite;
        nouveau->consommation = consommation;
        nouveau->hauteur = 1;
        nouveau->gauche = NULL;
        nouveau->droit = NULL;
        return nouveau;
    }

    // Comparaison pour insérer à gauche ou à droite
    if (strcmp(id, racine->id_station) < 0) {
        racine->gauche = inserer(racine->gauche, id, type, capacite, consommation);
    } else if (strcmp(id, racine->id_station) > 0) {
        racine->droit = inserer(racine->droit, id, type, capacite, consommation);
    } else {
        // Si l'ID existe, ajouter la consommation
        racine->consommation += consommation;
    }

    // Mettre à jour la hauteur de l'arbre
    racine->hauteur = obtenirHauteur(racine->gauche) > obtenirHauteur(racine->droit) ? obtenirHauteur(racine->gauche) : obtenirHauteur(racine->droit);
    racine->hauteur += 1;

    // Calculer l'équilibre
    int facteurEquilibre = calculerFacteurEquilibre(racine);

    // Rotation pour rééquilibrer l'arbre si nécessaire
    if (facteurEquilibre > 1) {
        if (strcmp(id, racine->gauche->id_station) < 0) {
            return rotationDroite(racine);
        }
    }

    if (facteurEquilibre < -1) {
        if (strcmp(id, racine->droit->id_station) > 0) {
            return rotationGauche(racine);
        }
    }

    return racine;
}








int main() {
    AVLNode* racine = NULL;

    // Insertion de quelques nœuds avec des valeurs fictives
    racine = inserer(racine, "1", "HV-B", 100, 200);
    racine = inserer(racine, "2", "HV-A", 150, 100);
    racine = inserer(racine, "3", "LV", 200, 50);

    // Afficher la consommation de chaque station
    printf("Consommation pour la station 1 : %d\n", racine->consommation);
    printf("Consommation pour la station 2 : %d\n", racine->droit->consommation);
    printf("Consommation pour la station 3 : %d\n", racine->gauche->consommation);

    return 0;
}
