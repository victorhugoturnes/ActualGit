#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n, i, grade, best, id;

	scanf("%d", &n);

	for (i = grade = id = 0; i < n; ++i)
	{
		scanf("%d", &grade);
		if(grade >= 8 && grade > best)
		{
			scanf("%d", &id);
		}else
		{
			scanf("%*d");
		}
	}
	if(id) printf("%d\n",id );
	else printf("Minimum note not reached\n");
	return 0;
}