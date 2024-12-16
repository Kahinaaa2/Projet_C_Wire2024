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

//fonction pour calculer le mininum
long min(long a, long b){	
   if(a>b){
     return b;
   }
   return a;
}

//fonction pour calculer le maximum
long max(long a, long b){     
   if(a>b){
     return a;
   }
   return b;
}
   
//création d'un AVL   
AVL* creerAVL(long nb, long cap, long conso){
	AVL* new = malloc(sizeof(AVL));
	if(new == NULL){
		exit (1);
	}
	
	new->identifiant = nb;	//identifiant de la station
	new->capacite = cap;	//capacité de la station
	new->consommation = conso;	//consommation 
	new->eq = 0;
	new->fg = NULL;
	new->fd = NULL;

	return new;
}

AVL* rotationDroite(AVL* a){
	if(a==NULL){
	  printf("err1\n");
	  exit(2);
	}  
	
	AVL* p = a->fg;
	int eq_a = a->eq;
	int eq_p = p->eq;

	a->fg = p->fd;
	p->fd = a;

	a->eq = eq_a - min(eq_p, 0) + 1; 
	p->eq = max(max(eq_a + 2, eq_a + eq_p + 2), eq_p + 1);

	return p; 
}

AVL* rotationGauche(AVL* a){
	if(a==NULL){
	  printf("err2\n");
	  exit(3);
	}  
	
	AVL* p = a->fd;
	int eq_a = a->eq;
	int eq_p = p->eq;

	a->fd = p->fg;
	p->fg = a;

	a->eq = eq_a - max(eq_p, 0) - 1;
	p->eq = min(min(eq_a - 2, eq_a + eq_p - 2), eq_p - 1);

	return p;
}

AVL* doubleRotationDroite(AVL* a){
	if(a==NULL){
	  printf("err3\n");
	  exit(4);
	} 
	a->fg = rotationDroite(a->fg);
	return rotationGauche(a);
}

AVL* doubleRotationGauche(AVL* a){
	if(a==NULL){
	  printf("err4\n");
	  exit(5);
	} 
	
	a->fd = rotationGauche(a->fd);
	return rotationDroite(a);
}

AVL* equilibreAVL(AVL* a){
	if(a==NULL){
	  printf("err5\n");
	  exit(6);
	} 

	if(a->eq <= -2){
		if(a->fg->eq <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}
	else if(a->eq >= 2){
		if(a->fd->eq >= 0){
			return rotationGauche(a);
		}
		else{
			return doubleRotationGauche(a);
		}
	}
	return a;
}	

AVL* insererAVL(AVL* a, long e, long v, long c, int *h){
	if(a == NULL){
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
	else if(e==a->identifiant){
		a->consommation += c;
		a->capacite +=v;
	}
	else {
		*h = 0; 
		return a; 
	}

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

void affiche(AVL* a){
   if(a!=NULL){
     affiche(a->fg);
     printf("%ld;%ld;%ld\n",a->identifiant,a->capacite,a->consommation);
     affiche(a->fd);
   }
}     

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
 	 station=insererAVL(station,v1,v2,v3,&h);
 	 //printf("%ld,%ld,%ld\n",v1,v2,v3);
  }	 
  
  affiche(station);
  libererAVL(station);
  
  return 0;
}  



	
