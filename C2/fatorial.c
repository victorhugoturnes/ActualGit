#include <stdio.h>

int fat(int n)
{
	return n>1 ? n*fat(n-1) : 1;
}

int fib1( int n ){
    int i=0,j=1,k;
    for(;n>0;n--){
        k=j;
        j+=i;
        i=k;
        // printf("i = %d j = %d k = %d\n", i, j, k );
        return j;
    }
}

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	printf("%d", fib1(n));
	return 0;
}