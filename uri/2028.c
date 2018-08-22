#include <stdio.h>

int main(){
    int num, loop, i, j;

    for ( loop = 1; !feof(stdin); loop++) {
        scanf("%d", &num);
        if(feof(stdin)) break;
        int temp =(int) (1 + (num + 1) * num / 2.0);
        printf("Caso %d: %d numero%s0",loop, temp, (temp > 1 ? "s\n" : "\n"));

        for (i = 0; i <= num; i++) {
            for (j = 0; j < i; j++) {
                printf(" %d", i);
            }
        }
        printf("\n\n");
    }
}