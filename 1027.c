#include <stdio.h>
#include <math.h>

typedef struct points
{
	int x, y, z;
} points;

void scanPoints(int cases, points *coords);
void cleanPoints(int cases, points *coords, points *odd, points *even);
void printer(points *odd, points *even, int cases);
int countSame(points *x);
int curveCount(points *x);
int countCases(points *x, int lim_i, int lim_j, int i);

int main()
{
	int cases, i, j, test;
	while(scanf("%d", &cases) == 1)
	{
		//if(cases == 0) break;
		points coords[cases], odd[cases], even[cases];
		scanPoints(cases, coords);
		for (i = 0; i < cases; ++i)
		{
			for(j=i; (coords[j].x <= coords[j-1].x || coords[j].y < coords[j-1].y) && j>0; --j)
			{
				points temp = coords[j];
				coords[j] = coords[j-1];
				coords[j-1] = temp;
			}
		}
		cleanPoints(cases, coords, odd, even);

		test = (int)fmax(curveCount(odd), curveCount(even));

		printf("%d\n", test );
	}
	return 0;
}
void scanPoints(int cases, points *coords)
{
	for (int i = 0; i < cases; ++i)
	{
		scanf("%d %d", &coords[i].x, &coords[i].y);
	}
}

void cleanPoints(int cases, points *coords, points *odd, points *even)
{
	int i, k=0, n=0;
	for (i = 0; i < cases; ++i)
	{
		if(coords[i].y%2)
		{
			odd[k] = coords[i];
			odd[0].z = ++k;
		}
		else
		{
			even[n] = coords[i];
			even[0].z = ++n;
		}

	}
}

void printer(points *odd, points *even, int cases)
{
	int i;
	for (i = 0; i < odd[0].z; ++i)
	{
		printf("odds[x][y]=[%d]	[%d]\n",odd[i].x, odd[i].y );
	}
	printf("\n");
		for (i = 0; i < even[0].z; ++i)
	{
		printf("even[x][y]=[%d]	[%d]\n",even[i].x, even[i].y );
	}
	printf("\n\n");
}

int countSame(points *x)
{
	int i=0;
	if(x[0].y != x[1].y) return 1;
	while(x[i].y == x[0].y)
	{
		i++;
	}
	return i;
}

int curveCount(points *x)
{
	int lim_i = 0, lim_j = 0, i, j, max = 0, current;
	while(lim_j < x[0].z)
	{
		i = lim_i;
		lim_i += countSame(&x[lim_i]);
		j = lim_i;
		lim_j = countSame(&x[lim_i]) + lim_i;
		if (x[i].y + 2 == x[lim_i].y)	current = countCases(x, lim_i, lim_j, i);
		if (current > max) max = current;
	}
	return max;
}

int countCases(points *x, int lim_i, int lim_j, int i)
{
	int j=lim_i, count=0, temp = i, hold = 0;
	while(i != lim_i && j != lim_j)
	{
		for ( i ; i < lim_i && x[i].x <= x[j].x; ++i);
		if(x[i].x > x[j].x)
		{
			count++;
		}
		for (j ; j < lim_j && x[i].x >= x[j].x ; ++j);
		if(x[i].x < x[j].x)
		{
			count++;
		}
	}
	i = lim_i-1;
	j = lim_j-1;
	while(i > temp && j > lim_i-1)
	{
		if(x[i].x > x[j].x)
		{
			hold++;
		}
		for ( i ; i > temp && x[i].x >= x[j].x; --i)
		{
		}
		if(x[i].x < x[j].x)
		{
			hold++;
		}
		if(x[i].x > x[j].x)
		{
			hold++;
		}
		for (j ; j > lim_i && x[i].x <= x[j].x ; --j)
		{
		}
	}
	return (int)fmax(hold, count);
}