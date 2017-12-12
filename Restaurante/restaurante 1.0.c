#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 128
#define MAXARRAY 1000

typedef struct _garcom _garcom;
typedef struct _data _data;
typedef struct _horario _horario;
typedef struct _item _item;
typedef struct _venda _venda;
typedef struct _comanda _comanda;

void readGarcon(_garcom **garcon, FILE *in);

char *readLine(char *line, FILE *in);

int load(_garcom **garcons, _item **itens, _comanda **comandas, _data *dia);

void readHorario(_horario horario, FILE *in);
void readDay(_data *dia, FILE *s);

typedef struct _data
{
	int  dia, mes, ano;
}_data;

typedef struct _horario
{
	int hora, minuto;
}_horario;

typedef struct _item
{
	char *nome;
	int total;
	double preco;
}_item;

typedef struct _venda
{
	_item *item;
	int quantidade;
}_venda;

typedef struct _comanda
{
	char mesa[10];
	int pessoas;
	_horario entrada, saida;
	_venda **consumo;
}_comanda;

typedef struct _garcom
{
	char *nome;
	_comanda *comanda;
}_garcom;


int main(int argc, char const *argv[])
{
	_data dia;
	_garcom **garcons;
	_item **itens;
	_comanda **comandas;

	if(!load(garcons, itens, comandas, &dia))
	{
		return 0;
	}
}

int load(_garcom **garcons, _item **itens, _comanda **comandas, _data *dia)
{
	FILE *stream = fopen("consumo.txt", "r");
	int i;

	if(!stream)
	{
		fprintf(stdout, "erro ao abrir o arquivo\n");
		return 0;
	}

	readDay(dia, stream);

	garcons = malloc(sizeof(_garcom*)*MAXARRAY);

	for (i = 0; i < feof(stream); ++i)
	{
		readGarcon(garcons, stream);
		// printf("%s\n", garcons[i]->nome);
		// readHorario(&garcons->comanda->entrada, stream);
		// readHorario(&garcons->saida, stream);
	}
	return 1;
}

void readDay(_data *dia, FILE *s)
{
	fscanf(s, " %d/%d/%d ", &dia->dia, &dia->mes, &dia->ano);
}

char *readLine(char *line, FILE *in)
{
	line = malloc(MAXSTRING*sizeof(char)+2); 				//buffer size
	fgets(line, MAXSTRING, in); 							//reads line
	line = realloc(line, strlen(line)*sizeof(char)); 	//reduce size to needed
	return line;
}

/*
void readHorario(_horario horario, FILE *in)
{
	fscanf(in, " %d:%d ", &horario->hora, &horario->minuto);
	fprintf(stderr, "%d:%d\n",horario->hora, horario->minuto);
}
*/

void readGarcon(_garcom **garcon, FILE *in)
{
	char buffer[MAXSTRING];
	readLine(buffer, in);
}