#include<stdio.h>
#include<stdlib.h>

typedef struct noeud {
    int valeur;
    struct noeud* gauche;
    struct noeud* droit;
} Noeud;

Noeud* createNoeud(int v) {
    Noeud* n = malloc(sizeof(Noeud));
    if (n == NULL) {
        exit(1);  // Erreur d'allocation mémoire
    }
    n->valeur = v;
    n->gauche = NULL;
    n->droit = NULL;
    return n;
}

void insertABR(Noeud** a, int e) {
    Noeud* new = createNoeud(e);
    if (new == NULL) {
        exit(2);  // Erreur d'allocation mémoire
    }
    if (*a == NULL) {
        *a = new;  // L'arbre est vide, on insère ici
        return;
    }

    // L'arbre n'est pas vide
    Noeud* tmp = *a;
    while (1) {
        if (new->valeur > tmp->valeur) {
            if (tmp->droit == NULL) {
                tmp->droit = new;
                break;
            } else {
                tmp = tmp->droit;
            }
        } else if (new->valeur < tmp->valeur) {
            if (tmp->gauche == NULL) {
                tmp->gauche = new;
                break;
            } else {
                tmp = tmp->gauche;
            }
        } else {
            // Si la valeur existe déjà, on ne l'insère pas
            break;
        }
    }
}

// Fonction pour afficher l'ABR avec les liens gauche/droit
void afficherABR(Noeud* a, int level) {
    if (a != NULL) {
        // Affichage du sous-arbre droit
        afficherABR(a->droit, level + 1);
        // Affichage de l'élément
        for (int i = 0; i < level; i++) {
            printf("   ");  // Espaces pour le niveau d'indentation
        }
        printf("%d\n", a->valeur);
        // Affichage du sous-arbre gauche
        afficherABR(a->gauche, level + 1);
    }
}

int parcoursPrefixeRecherche(Noeud* a, int e, int* noeudsParcourus) {
    if (a == NULL) {
        return 0; // L'arbre est vide
    }
    (*noeudsParcourus)++; // Incrémenter le compteur de nœuds parcourus
    if (a->valeur == e) {
        printf("Élément %d trouvé au bout de %d nœuds (parcours préfixe).\n", e, *noeudsParcourus);
        return 1;
    }
    // Rechercher dans le sous-arbre gauche
    if (parcoursPrefixeRecherche(a->gauche, e, noeudsParcourus)) {
        return 1; // Trouvé dans le sous-arbre gauche
    }
    // Rechercher dans le sous-arbre droit
    if (parcoursPrefixeRecherche(a->droit, e, noeudsParcourus)) {
        return 1; // Trouvé dans le sous-arbre droit
    }
    return 0; // L'élément n'est pas dans l'arbre
}


Noeud *minimum(Noeud *a){                          
  Noeud *tmp;
  if(a==NULL){
    return NULL;
  }
  tmp=a;
  while(tmp->gauche!=NULL){
    tmp=tmp->gauche;
  }
  return tmp;
}

Noeud *maximum(Noeud *a){
  Noeud *tmp;
  if(a==NULL){
    return NULL;
  }
  tmp=a;
  while(tmp->droit!=NULL){
    tmp=tmp->droit;
  }
  return tmp;
}



//supprimer un noeud

//fonction de suppression
Noeud *supNoeud(Noeud *a, int e){
    if(a==NULL){
        //si l'arbre est vide rien a sup
        return a;
    }
    if(e<a->valeur){
        //l'element a supp est dans le sous arbre gauche
        a->gauche = supNoeud(a->gauche, e);
    }
    else if(e>a->valeur){
        //l'element a supp est dans le sous arbre droit
        a->droit = supNoeud(a->droit, e);
    }
    else{
        //cas ou on trouve le noeud a supp
        if(a->gauche == NULL && a->droit == NULL){
            //le noeud a sup est une feuille
            free(a);
            a=NULL;
            return a;
        }
        else if(a->gauche == NULL){
            //le noeud a sup a un seul fils droit
            Noeud *tmp = a;
            a=a->droit;
            free(a);
            return tmp;
        }
        else if(a->droit==NULL){
            //le neoud a sup a un seul fils gauche
            Noeud *tmp = a;
            a=a->gauche;
            free(a);
            return tmp;
        }
        else{
            //le neoud a deux enfants
            Noeud*min = Min(a->droit);//trouver le minimum du sous abre droit
            a->valeur = min->valeur;
            a->droit = supNoeud(a->droit, min->valeur);
        }
    }
    return a;
}
