#include<stdio.h>
#include<stdlib.h>

typedef struct AVL{
    int identifiant;
    int conso;
    int capacite;
    int eq;
    int hauteur;
    struct AVL *fg;
    struct AVL *fd;
}AVL;

AVL *creationAVL(int nombre, int cap, int conso){
    AVL *new = malloc(sizeof(AVL));
    if (new==NULL){
        exit(1);
    }
    new->identifiant = nombre;
    new->capacite = cap;
    new->conso = conso;
    new->fg = NULL;
    new->fd = NULL;

    return new;
}

AVL *insererAVL(AVL *a, int e, int v, int c){
        if(a==NULL){
            a=creationAVL(e,v,c);
            return a;
        }
        if(e<a->identifiant){
            a->fg = insererAVL(a->fg, e,v,c);
        }
        if(e<a->identifiant){
            a->fg = insererAVL(a->fd, e,v,c);
        }
        if(e=a->identifiant){
            a->conso += c;
            a->capacite += v;
        }
    return a;
} 

int hauteur(AVL *a) {
    if (a == NULL)
        return 0; // Un nœud NULL a une hauteur de 0
    return a->hauteur;
}

int facteur_eq(AVL *a) {
    if (a == NULL)
        return 0;
    return hauteur(a->fg) - hauteur(a->fd);
}


void production(AVL *a, int *somme) {
    if (a == NULL) {
        return;
    }

    // Vérifie la production de la station actuelle
    if (a->capacite < a->conso) {
        printf("La station %d est en sous-production d'énergie.\n", a->identifiant);
    } else if (a->capacite > a->conso) {
        printf("La station %d est en surproduction d'énergie.\n", a->identifiant);
    } else {
        printf("La station %d est équilibrée en production et consommation.\n", a->identifiant);
    }

    // Ajoute la capacité à la somme totale
    *somme += a->capacite;

    // Appelle la fonction pour les sous-arbres gauche et droit
    production(a->fg, somme);
    production(a->fd, somme);
}


void calculEtSortie(AVL *a, int *capaciteTotale, int *consoTotale) {
    if (a == NULL) {
        return; // Condition d'arrêt pour la récursivité
    }

    // Parcours récursif à gauche
    calculEtSortie(a->fg, capaciteTotale, consoTotale);

    // Calculer les sommes
    *capaciteTotale += a->capacite;
    *consoTotale += a->conso;

    // Afficher les données pour le shell (par exemple)
    printf("Station %d : Capacite=%d, Conso=%d\n", a->identifiant, a->capacite, a->conso);

    // Parcours récursif à droite
    calculEtSortie(a->fd, capaciteTotale, consoTotale);
}

AVL *lireEtTraiterDonnees(AVL *station) {
    char v1, v2, v3;

    while (scanf("%c;%c;%c\n", &v1, &v2, &v3) == 3) {
        // Traitement des caractères v2 et v3
        if (v2 == '-') {
            v2 = 0; // Interprétation de '-' comme 0
        }
        if (v3 == '-') {
            v3 = 0; // Interprétation de '-' comme 0
        }
        // Vérification de la validité des données
        if ((v2 != 0 && v2 < '0') || (v3 != 0 && v3 < '0')) {
            printf("Problème dans les données récupérées\n\n");
        }

        // Insertion dans l'AVL
        station = insererAVL(station, v1, v2, v3);
    }

    return station;
}


int main() {
    char v1, v2, v3;
    int sum2 = 0;
    int sum3 = 0;
    int capaciteTotale = 0;
    int consoTotale = 0;
    AVL *station = NULL;



    // Parcours de l'arbre AVL pour calculer les sommes
    parcoursAVL(station, &sum2, &sum3);

    // Affichage des résultats finaux
    printf("0;%d;%d\n", sum2, sum3);


    // Parcourir l'AVL, calculer les totaux et afficher pour le shell
    printf("Début du rapport des stations :\n");
    calculEtSortie(station, &capaciteTotale, &consoTotale);
    lireEtTraiterDonnees(station);
    // Affichage final des totaux
    printf("Somme totale : Capacite=%d, Conso=%d\n", capaciteTotale, consoTotale);

    return 0;
}

