#include <stdio.h>
#include <stdlib.h>

typedef struct AVL {
	int identifiant; 
	int conso;
	int capacite;
	int eq;
	struct AVL* fg;
	struct AVL* fd;
}AVL; 


AVL* creationAVL(int nombre, int cap, int conso){
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

	AVL* p = a->fg
	int eqa = a->eq;
	int eqp = p->eq;

	a->fg = p->fd;
	p->fd = a;

	a->eq = eqa - min(eqp, 0) + 1; 
	p->eq = max(max(eqa + 2, eqa + eqp + 2), eqp + 1);

	return p; 
}

AVL* rotationGauche(AVL* a){
	
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
	
	a->fg = rotationDroite(a->fg);
	return rotationGauche(a);
}

AVL* doubleRotationGauche(AVL* a){
	
	a->fd = rotationGauche(a->fd);
	return rotationDroite(a);
}

AVL* equilibreAVL(AVL* a){

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

AVL* insererAVL(AVL* a, int e, int v, int c, int *h){
	if(a == NULL){
		*h = 1;
		a=creationAVL(e, v, c);
		return a;
	}
	
	else if(e<a->identifiant){
		a->fg = insererAVL(a->fg, e, v, c);
		*h = -*h;
	}

	else if(e>a->identifiant){
		a->fd = insererAVL(a->fd, e, v, c);
	}
	
	else if(e=a->identifiant){
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

	return a;
}

void production (AVL* a){
	if (a == NULL){
		return;
	}
	if (a->capacite < a->conso){
		printf("La station est en sous-production d'énergie");
	} else if (a->capacite > a->conso){
		printf("La station est en surproduction d'énergie");
	} else {
		printf("La station est en équilibre");
	}
	
	production(a->fg);
	production(a->fd);

}

void recuperationDonnees(AVL* a, FILE* f){
	
	if (a == NULL){
		exit(3);
	}

	fprintf(f, "Station : %d,capacite : %d,  Consommation : %d\n", a->identifiant, a->capacite, a->conso); 

	recuperationDonnees(a->fg, f);
	recuperationDonnees(a->fd, f);

}

int main(){
    	char v1, v2, v3;
    	int sum2=0;
    	int sum3=0;
        int h = 0;

 	AVL* station = NULL; 
	FILE* f = fopen("consommations.txt", "r");

	if(f == NULL){
		printf("Erreur lors de l'ouverture du fichier\n");
		exit(4);
	}


    while(scanf("%c;%c;%c\n", &v1,&v2,&v3)==3){

	    
  /*      if(v1==0){
            sum2+=v2;
            sum3+=v3;
        }
    }
    printf("0;%d;%d\n",sum2, sum3); */

    	if(v2 == '-'){
    	  v2 = 0;
    	}
    	else if(v3 == '-'){
    	  v3 = 0;
    	}
    	else{ 
    	  printf("problème dans les données récupérées\n\n");
    	}    

    	station = insererAVL(station, v1, v2, v3, h);
    	
	}

	production(station);

	recuperationDonnees(station, f);
	
	fclose(f);

	printf("Les données sont enregistrées dans le fichier");

    return 0;
}


    	//il faut qu'on parcourt avl et scanf les donnees somme puis les donner au shell
    	//verifier la recup des donnees du shell
    	//robustesse du programme
    	



	

