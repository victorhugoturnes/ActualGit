#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



void stacks(int n);

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	stacks(0);
	return 0;
}

void stacks(int n)
{
	for (int i = 0; i < 20000; ++i)
	{
		rand()%2 ? printf("/") : printf("\\");

	}
}