#include <stdio.h>
#include <math.h>

int inverte(int n);

int main(int argc, char const *argv[])
{
	printf("%d", inverte(1234));
	return 0;
}

int inverte(int n)
{
	int aux = log10(n);
	if(n)
	{
		return inverte(n/10)+pow(10,aux)*(n%10);
	}else return 0;
}