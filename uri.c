#include <stdio.h>

int main(){
    int i,j;
    double nota1, nota2;
    double media = 0.0;

    i = 0;

    while(i < 2){
    scanf("%lf",&i);
    if(i > 0.0 && i < 10.0){
        media = (nota1 + nota2)/ 2.0;
        printf("media = %.2lf\n",media);
    } else{
        printf("nota invalida\n");
    }
        i++;
    }
}