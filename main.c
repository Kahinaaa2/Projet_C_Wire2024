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
