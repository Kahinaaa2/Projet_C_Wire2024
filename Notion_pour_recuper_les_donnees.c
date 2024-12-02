int main(){
    int v1, v2, v3;
    int sum2=0;
    int sum3=0;
    while(scanf("%d;%d;%d\n", &v1,&v2,&v3)==3){
    //printf("%d %d %d \n", v1,v2,v3);
        if(v1==0){
            sum2+=v2;
            sum3+=v3;
        }
    }
    printf("0;%d;%d\n",sum2, sum3);
    return 0;
}
