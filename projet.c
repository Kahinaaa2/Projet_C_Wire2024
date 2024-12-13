#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct AVL {
	long identifiant; 
	long conso;
	long capacite;
	int eq;
	struct AVL* fg;
	struct AVL* fd;
}AVL; 

long min(long a, long b){
  
   if(a > b){
     return b;
   }
   return a;
}

long max(long a, long b){     

   if(a > b){
     return a;
   }
   return b;
}
   


AVL* creationAVL(long nombre, long cap, long conso){
	AVL* new = malloc(sizeof(AVL));
	if(new == NULL){
		exit (1);
	}
	
	new->identifiant = nombre;
	new->capacite = cap;
	new->conso = conso;
	new->eq = 0;
	new->fg = NULL;
	new->fd = NULL;

	return new;
}

AVL* rotationDroite(AVL* a){

	AVL* p = a->fg;
	int eqa = a->eq;
	int eqp = p->eq;

	a->fg = p->fd;
	p->fd = a;

	a->eq = eqa - min(eqp, 0) + 1; 
	p->eq = max(max(eqa + 2, eqa + eqp + 2), eqp + 1);

	return p; 
}

AVL* rotationGauche(AVL* a){
	if(a==NULL){
	  printf("err2\n");
	  exit(2);
	}  
	
	AVL* p = a->fd;
	int eqa = a->eq;
	int eqp = p->eq;

	a->fd = p->fg;
	p->fg = a;

	a->eq = eqa - max(eqp, 0) - 1;
	p->eq = min(min(eqa - 2, eqa + eqp - 2), eqp - 1);

	return p;
}

AVL* doubleRotationDroite(AVL* a){
	if(a==NULL){
	  printf("err3\n");
	  exit(3);
	} 
	a->fg = rotationDroite(a->fg);
	return rotationGauche(a);
}

AVL* doubleRotationGauche(AVL* a){
	if(a==NULL){
	  printf("err4\n");
	  exit(4);
	} 
	
	a->fd = rotationGauche(a->fd);
	return rotationDroite(a);
}

AVL* equilibreAVL(AVL* a){


	if(a==NULL){
	  printf("err5\n");
	  exit(5);
	} 

	if(a->eq <= -2){
		if(a->fg->eq <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}else if(a->eq >= 2){
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
		a=creationAVL(e, v, c);
		
		if(a==NULL){
	 	   printf("err6\n");
	 	   exit(6);
		} 
		
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
		a->conso += c;
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
		}else{
			*h = 1;
		}
	}	

	return a;
}

void affiche(AVL* a){
   if(a!=NULL){
     affiche(a->fg);
     printf("%ld;%ld;%ld\n",a->identifiant,a->capacite,a->conso);
     affiche(a->fd);
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
  
  return 0;
}  



    	



	
