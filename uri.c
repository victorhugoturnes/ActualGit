#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n, i, id, bestid;
	double grade = 0, best = 0;

	scanf("%d", &n);

	for (i = bestid = 0; i < n; ++i)
	{
		scanf("%d %lf", &id, &grade);
		if(grade >= 8 && grade > best)
		{
			best = grade;
			bestid = id;
		}
	}
	if(bestid) printf("%d\n",bestid );
	else printf("Minimum note not reached\n");
	return 0;
}