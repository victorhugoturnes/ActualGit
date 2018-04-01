#include <stdio.h>
#include <math.h>

int fac(int n) // questao 1
{
	return n ? n*fac(n-1) : 1;
}

int fib(int n) // questao 2
{
	return n <= 1 ? n : fib(n-1) + fib(n-2);
}

int inv(int n) //questao 3
{
	return n ? n%10*pow(10, (int)log10(n)) + inv(n/10) : 0;
}

int sumVet(int *n, int size) //questao 4
{
	return size ? n[0] + sumVet(n+1, size-1) : 0;
}

int sumN(int n)  //questao 5
{
	return n ? sumN(n-1) + n : 0;
}

int notPow(int base, int exp) //questao 6
{
	return exp ? base*notPow(base, exp-1) : 1;
}

int invV(int *v, int size) //questao 7
{
	v[0] += v[size-1] - (v[size-1] = v[0]);
	return size > 4 ? invV(v+1, size-2) : 0;
}

int gcd(int x, int y) //questao 8
{
	return y ? gcd(y, x%y) : x;
}

int dig(int n, int digi) //questao 9
{
	return n ? (n%10==digi) + dig(n/10, digi) : 0;
}

int soma(int x, int y) //questao 10
{
	return y ? x + soma(x, y-1) : 0;
}

int locate(int *v, int size, int find) //questao 11
{
	if(v[0] == find) return 1;
	return size ? locate(v+1, size-2, find) : 0;
}

int main()
{
	int n, v[10], i, m;

	scanf("%d", &n);
	scanf("%d", &m);


	for (i = 0; i < n; ++i)
	{
		v[i] = i;
	}
/*
	invV(v, n);

	for (i = 0; i < n; ++i)
	{
		printf("%d\n", v[i] );
	}
*/
	printf("%d\n", locate(v, n, m));
    return 0;
}
