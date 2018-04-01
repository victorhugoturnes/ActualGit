#include <stdio.h>
#include <math.h>

int fac(int n)
{
	return n ? n*fac(n-1) : 1;
}

int fib(int n)
{
	return n <= 1 ? n : fib(n-1) + fib(n-2);
}

int inv(int n)
{
	return n ? n%10*pow(10, (int)log10(n)) + inv(n/10) : 0;
}

int sumVet(int *n, int size)
{
	return size ? n[0] + sumVet(n+1, size-1) : 0;
}

int sumN(int n)
{
	return n ? sumN(n-1) + n : 0;
}

int notPow(int base, int exp)
{
	return exp ? base*notPow(base, exp-1) : 1;
}

int invV(int *v, int size)
{
	v[0] += v[size-1] - (v[size-1] = v[0]);
	return size > 4 ? invV(v+1, size-2) : 0;
}

int main()
{
	int n, v[10], i, m;

	scanf("%d", &n);
//	scanf("%d", &m);

	for (i = 0; i < n; ++i)
	{
		scanf("%d", &v[i]);
	}

	invV(v, n);

	for (i = 0; i < n; ++i)
	{
		printf("%d\n", v[i] );
	}

    return 0;
}
