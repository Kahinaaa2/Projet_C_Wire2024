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



