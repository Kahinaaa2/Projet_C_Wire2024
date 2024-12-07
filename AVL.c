#include<stdio.h>
#include<stdlib.h>

//création du noeud
typedef struct noeud {
    int valeur;
    struct noeud*gauche;
    struct noeud*droit;
    int hauteur;//stocker la hauteur pour les calculs d'equilibrage
}Noeud;

Noeud*creationNoeud(int val){
    Noeud*new=malloc(sizeof(Noeud));
    if(new==NULL){
        exit(1);
    }
    new->valeur=val;
    new->gauche=NULL;
    new->droit=NULL;
    new->hauteur=1;//initialement un nouveau noeud est une feuille
    return new;
}

void hauteur(Noeud *a,int* hauteur){ //hauteur initialiser à 1
   if(a->droit != NULL){
     *hauteur++;
     hauteur(a->droit,hauteur);
   }
   if(a->gauche != NULL){
     *hauteur++;
     hauteur(a->gauche,hauteur);
   }
}

//etape 1 : modifier la structure pour inclure le facteur d'equilibre
typedef struct noeud{
    int valeur;
    int equilibre;
    struct noeud*gauche;
    struct noeud*droit;
}Noeud;

Noeud *creationNoeud(int e){
    Noeud *new=malloc(sizeof(Noeud));
    if(new==NULL){
        exit(1);
    }
    new->valeur=e;
    new->gauche=NULL;
    new->droit=NULL;
    new->equilibre=0;
    return new;
}

//rotation gauche
Noeud *rotationGauche(Noeud *a){
    if(a==NULL || a->droit == NULL){
        return a;//rien a faire si le noeud ou son fils droit est NULL
    }
    //realisation de la rotation
    Noeud *b = a->droit; //le fils droit devient le noeud de la racine
    a->droit = b->gauche; //le sous arbre gauche de b devient le sous arbre droit de a
    b->gauche = a; //a devient le fils gauche de b
    //mise a jour du facteur d'equilibrage
    a->equilibre=0;
    b->equilibre=0;

    return b;//retourner la nouvelle racine
}

//rotation droite
Noeud *rotationDroite(Noeud *a){
    if(a==NULL || a->gauche ==NULL){
        return a;
    }
    Noeud *b = a->gauche;
    a->gauche = b->droit;
    b->droit =a;

    a->equilibre = 0;
    b->equilibre =0;
    return b;
}

//etape 4 test des rotation
// je m'appelle Kahino et je suis un passioné d'informatique
void test rotations(){
    
}