#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
#define MAXSTRING 100
#define ANO 2017

typedef struct _carro _carro;

char *readLine(FILE *in);
int load(_carro *revendedora[]);
void printer(struct _carro *carro, FILE *stream);
void ipva(_carro *revendedora[]);
void close(_carro *revendedora[]);


typedef struct _carro
{
	char *modelo;
	int ano;
	char *cor;
	double preco;
}_carro;

int main(int argc, char const *argv[])
{
	int i;
	double preco;
	_carro *revendedora[MAXSIZE];

	if(!load(revendedora))
	{
		printf("error opening file\n");
	 	return 0;
	}
/*
	for (i = 0; revendedora[i]; ++i)
	{
		printer(revendedora[i], stdout);
	}
*/
	ipva(revendedora);
	close(revendedora);
	return 0;
}

int load(_carro *revendedora[])
{
	int i;
	FILE *stream = fopen("carros.txt", "r");

	if(!stream) return 0;

	for (i = 0; !feof(stream); ++i)
	{
		revendedora[i] = malloc(sizeof(_carro));

		revendedora[i]->modelo = readLine(stream);
		fscanf(stream, " %d ", &revendedora[i]->ano);
		revendedora[i]->cor = readLine(stream);
		fscanf(stream, " %lf ", &revendedora[i]->preco);
		revendedora[i+1] = NULL;
	}
	return 1;
}

char *readLine(FILE *in)
{
	char *line = malloc((MAXSTRING+2)*sizeof(char));	//buffer size
	fgets(line, MAXSTRING, in); 							//reads line
	line = realloc(line, strlen(line)*sizeof(char)); 	//reduce size to needed
	return line;
}

void printer(struct _carro *carro, FILE *stream)
{
	fprintf(stream, "%s%d\n%s%.2lf\n\n", carro->modelo, carro->ano, carro->cor, carro->preco );
}

void ipva(_carro *revendedora[])
{
	int i;
	for ( i = 0; revendedora[i]; ++i)
	{
		if(revendedora[i]->ano < ANO-20) printf("IPVA = %lf\n",0.0);
		else if(revendedora[i]->ano < ANO-10) printf("IPVA = %lf\n", revendedora[i]->preco*0.015 );
		else printf("IPVA = %lf\n", revendedora[i]->preco*0.025 );
		printer(revendedora[i], stdout);
	}
}

void close(_carro *revendedora[])
{
	for (int i = 0; revendedora[i]; ++i)
	{
		free(revendedora[i]->modelo);
		free(revendedora[i]->cor);
		free(revendedora[i]);
	}
}