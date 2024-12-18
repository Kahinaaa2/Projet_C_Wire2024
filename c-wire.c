#include <stdio.h>
#include <stdlib.h>

//structure de l'AVL
typedef struct AVL { 
	long identifiant; 
	long consommation;
	long capacite;
	int eq;	//facteur d'équilibre
	struct AVL* fg;
	struct AVL* fd;
}AVL; 

//fonction pour calculer le mininum entre deux valeurs
long min(long a, long b){	
   if(a>b){
     return b;
   }
   return a;
}

//fonction pour calculer le maximum entre deux valeurs 
long max(long a, long b){     
   if(a>b){
     return a;
   }
   return b;
}
   
//création d'un nouveau noeud d'AVL   
AVL* creerAVL(long nb, long cap, long conso){
	AVL* new = malloc(sizeof(AVL));
	if(new == NULL){
		printf("Allocation échouée");
		exit (1);
	}
	
	new->identifiant = nb;	//identifiant de la station
	new->capacite = cap;	//capacité de transfert de la station
	new->consommation = conso;	//consommation des clients 
	new->eq = 0;
	new->fg = NULL;
	new->fd = NULL;

	return new;
}
//simple rotation droite 
AVL* rotationDroite(AVL* a){
	if(a==NULL){
	  printf("err1\n");
	  exit(2);
	}  
	
	AVL* pivot = a->fg; //le fils gauche est le pivot 
	int eq_a = a->eq;
	int eq_p = pivot->eq;

	a->fg = pivot->fd;
	pivot->fd = a;
	//mise à jour des facteurs d'équilibre 
	a->eq = eq_a - min(eq_p, 0) + 1; 
	pivot->eq = max(max(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);

	return pivot; 
}
//simple rotation gauche
AVL* rotationGauche(AVL* a){
	if(a==NULL){
	  printf("err2\n");
	  exit(3);
	}  
	
	AVL* pivot = a->fd; //le fils droit est le pivot
	int eq_a = a->eq;
	int eq_p = pivot->eq;

	a->fd = pivot->fg;
	pivot->fg = a;
	//mise à jour des facteurs d'équilibre 
	a->eq = eq_a - max(eq_p, 0) - 1;
	pivot->eq = min(min(eq_a - 2, eq_a + eq_p - 2), eq_p - 1);

	return pivot;
}
//double rotation droite 
AVL* doubleRotationDroite(AVL* a){
	if(a==NULL){
	  printf("err3\n");
	  exit(4);
	} 
	a->fg = rotationDroite(a->fg); 
	return rotationGauche(a); 
}
//double rotation gauche
AVL* doubleRotationGauche(AVL* a){
	if(a==NULL){
	  printf("err4\n");
	  exit(5);
	} 
	
	a->fd = rotationGauche(a->fd); //rotation 
	return rotationDroite(a);
}
//fonction pour équilibrer l'AVL
AVL* equilibreAVL(AVL* a){
	if(a==NULL){
	  printf("err5\n");
	  exit(6);
	} 

	if(a->eq <= -2){ // sous-arbre gauche déséquilibré
		if(a->fg->eq <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}
	else if(a->eq >= 2){ // sous-arbre droit déséquilibré
		if(a->fd->eq >= 0){
			return rotationGauche(a);
		}
		else{
			return doubleRotationGauche(a);
		}
	}
	return a;
}	
//fonction d'insertion dans un AVL
AVL* insererAVL(AVL* a, long e, long v, long c, int *h){
	if(a == NULL){ //si l'arbre est vide, on le creé 
		*h = 0;
		a=creerAVL(e, v, c);	
		return a;
	}
	else if(e<a->identifiant){
		a->fg = insererAVL(a->fg, e, v, c, h);
		*h = -(*h);
	}
	else if(e>a->identifiant){
		a->fd = insererAVL(a->fd, e, v, c, h);
	}
	else if(e==a->identifiant){ //mise à jour des valeurs si l'identifiant existe déjà
		a->consommation += c;
		a->capacite +=v;
	}
	else {
		*h = 0; 
		return a; 
	}
	//rééquilibrage
	if(*h != 0){
		a->eq += *h;
		a = equilibreAVL(a);

		if(a->eq == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}	
	return a;
}
//fonction pour afficher les données de chaque noeud de l'AVL
void affiche(AVL* a){
   if(a!=NULL){
     affiche(a->fg);
     printf("%ld;%ld;%ld\n",a->identifiant,a->capacite,a->consommation);
     affiche(a->fd);
   }
}     
//fonction pour libérer la mémoire allouée
void libererAVL(AVL* a){
	if(a!=NULL){
		libererAVL(a->fg);
		libererAVL(a->fd);
		free(a);
	}
}

int main(){
  long v1,v2,v3;
  AVL* station = NULL;
  int h = 0;

  while(scanf("%ld;%ld;%ld\n",&v1,&v2,&v3) == 3){
	  //validation des entrées
	  if(v1<0||v2<0||v3<0){
		  printf("Données incorrectes");
		  exit(7);
	  }
 	 station=insererAVL(station,v1,v2,v3,&h);
  }	 
  
  affiche(station);
  libererAVL(station);
  
  return 0;
}  



	
