#include<stdio.h>
#include<stdlib.h>

typedef struct AVL {
	long id; 
	long conso;
	long cap;
	int equ;
	struct AVL* d;
	struct AVL* g;
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
   


AVL* creationAVL(long nb, long cap, long conso){
	AVL* new = malloc(sizeof(AVL));
	if(new == NULL){
		exit (1);
	}
	
	new->id =nb;
	new->cap = cap;
	new->conso = conso;
	new->equ = 0;
	new->g = NULL;
	new->d = NULL;

	return new;
}

AVL* rotationDroite(AVL* a){

	AVL* p = a->g;
	int eqa = a->equ;
	int eqp = p->equ;

	a->g = p->d;
	p->d = a;

	a->equ = eqa - min(eqp, 0) + 1; 
	p->equ = max(max(eqa + 2, eqa + eqp + 2), eqp + 1);

	return p; 
}

AVL* rotationGauche(AVL* a){
	if(a==NULL){
	  printf("err2\n");
	  exit(2);
	}  
	
	AVL* p = a->d;
	int eqa = a->equ;
	int eqp = p->equ;

	a->d = p->g;
	p->g = a;

	a->equ = eqa - max(eqp, 0) - 1;
	p->equ = min(min(eqa - 2, eqa + eqp - 2), eqp - 1);

	return p;
}

AVL* doubleRotationDroite(AVL* a){
	if(a==NULL){
	  printf("err3\n");
	  exit(3);
	} 
	a->g = rotationDroite(a->g);
	return rotationGauche(a);
}

AVL* doubleRotationGauche(AVL* a){
	if(a==NULL){
	  printf("err4\n");
	  exit(4);
	} 
	
	a->d = rotationGauche(a->d);
	return rotationDroite(a);
}

AVL* equilibreAVL(AVL* a){


	if(a==NULL){
	  printf("err5\n");
	  exit(5);
	} 

	if(a->equ <= -2){
		if(a->g->equ <= 0){
			return rotationDroite(a);
		}
		else{
			return doubleRotationDroite(a);
		}
	}else if(a->equ >= 2){
		if(a->d->equ >= 0){
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
	
	else if(e<a->id){
		a->g = insererAVL(a->g, e, v, c, h);
		*h = -(*h);
	}

	else if(e>a->id){
		a->d = insererAVL(a->d, e, v, c, h);
	}
	
	else if(e==a->id){
		a->conso += c;
		a->cap +=v;
	}
	
	else {
		*h = 0; 
		return a; 
	}

	if(*h != 0){
	
		a->equ += *h;
		a = equilibreAVL(a);

		if(a->equ == 0){
			*h = 0;
		}else{
			*h = 1;
		}
	}	

	return a;
}

void affiche(AVL* a){
   if(a!=NULL){
     affiche(a->g);
     printf("%ld;%ld;%ld\n",a->id,a->cap,a->conso);
     affiche(a->d);
   }
}     

int main(){
  long a1,a2,a3;
  AVL* stat = NULL;
  int h = 0;

      while(scanf("%ld;%ld;%ld\n",&a1,&a2,&a3) == 3){
     	 station=insererAVL(station,a1,a2,a3,&h);
     	 //printf("%ld,%ld,%ld\n",a1,a2,a3);
      }	 
      
  affiche(stat);
  
  return 0;
}  

