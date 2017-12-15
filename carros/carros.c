#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAXSIZE 100
#define MAXSTRING 100
#define ANO 2017

typedef struct _carro _carro;

// functions

char *readLine(FILE *in);
int load(char fileName[], _carro *revendedora[]);
void printer(struct _carro *carro, FILE *stream);
void ipva(_carro *revendedora[]);
void close(_carro *revendedora[]);
void getPriceUnder(double preco, _carro* revendedora[]);

// structs

typedef struct _carro {
	char *modelo;
	int ano;
	char *cor;
	double preco;
} _carro;

int main(int argc, char const *argv[]) {
	int i;
	double preco;
	_carro *revendedora[MAXSIZE];

	setlocale(LC_ALL, "Portuguese");

	if(load("carros.txt", revendedora)) {
		printf("error opening file\n");
	 	return 0;
	}

	// DEBUG
	for (i = 0; revendedora[i]; ++i) {
		printer(revendedora[i], stdout);
	}

	printf("Insira o preço máximo desejado: ");
	scanf("%lf", &preco);

	getPriceUnder(preco, revendedora);

	ipva(revendedora);
	close(revendedora);

	return 0;
}

int load(char fileName[], _carro *revendedora[]) {
	int i;
	FILE *stream = fopen(fileName, "r");

	if(!stream) return 1;

	for (i = 0; !feof(stream); ++i) {
		revendedora[i] = malloc(sizeof(_carro));

		revendedora[i]->modelo = readLine(stream);
		fscanf(stream, " %d ", &revendedora[i]->ano);
		revendedora[i]->cor = readLine(stream);
		fscanf(stream, " %lf ", &revendedora[i]->preco);
		revendedora[i+1] = NULL;
	}
	return 0;
}

char *readLine(FILE *in) {
	char *line = malloc((MAXSTRING+2)*sizeof(char));	//buffer size
	//fgets(line, MAXSTRING, in); 						//reads line
	fscanf(in, "%[^\n]%*c", line);
	line = realloc(line, strlen(line)*sizeof(char)); 	//reduce size to needed
	return line;
}

void printer(_carro *carro, FILE *stream) {
	fprintf(stream, "%s\n", carro->modelo);
	fprintf(stream, "ANO %d\n", carro->ano);
	fprintf(stream, "R$%.2lf\n", carro->preco);
	fprintf(stream, "--------\n");
	//fprintf(stream, "%s%d\n%sR$%.2lf\n\n", carro->modelo, carro->ano, carro->cor, carro->preco );
}

void getPriceUnder(double preco, _carro* revendedora[]) {
	int i;

	for (i = 0; revendedora[i]; ++i) {
		if(revendedora[i]->preco <= preco) printer(revendedora[i], stdout);
	}
}

void ipva(_carro *revendedora[]) {
	int i;
	for ( i = 0; revendedora[i]; ++i) {
		if(revendedora[i]->ano < ANO-20) printf("IPVA = R$0.00\n");
		else if(revendedora[i]->ano < ANO-10) printf("IPVA = R$%.2lf\n", revendedora[i]->preco*0.015);
		else printf("IPVA = R$%.2lf\n", revendedora[i]->preco*0.025);
		printer(revendedora[i], stdout);
	}
}

void close(_carro *revendedora[]) {
	int i;

	for (i = 0; revendedora[i]; ++i) {
		free(revendedora[i]->modelo);
		free(revendedora[i]->cor);
		free(revendedora[i]);
	}
}