#include <stdio.h>
#include <math.h>
#include <string.h>

int palin(char *str, int size);
int expFac(int num, int exp);
int somaDigs(int n);
int subConj(char *str);

int main(int argc, char const *argv[])
{
	char str[200];
	// printf("%d", expFac(4, 4));
	// printf("%d\n",somaDigs(1234) );
	//gets(str);
	subConj("abc\0");
	return 0;
}

int subConjRec(char *str, int count)
{
	int i;
	if(count) subConjRec(str, count-1);
	printf("%d -- ",count );

	printf("{");
	for (i = 0; str[i]; ++i)
	{
		if(i & count) printf("%c ", str[i] );
	}
	printf("}\n");
}

int subConj(char *str)
{
	subConjRec(str, pow(2, strlen(str))-1);
}

int expFac(int num, int exp) //questao 5?
{
	if(num == exp) return pow(num, expFac(num, exp-1));
	return exp ? exp * expFac(num, exp-1) : 1;
}

int somaDigs(int n) //questao 3
{
	return n ? n%10 + somaDigs(n/10) : 0;
}

int palin(char *str, int size)
{
	if(size>1) return str[0] == str[size-1] ? palin(++str, size-2) : 0;
	return 1;
}