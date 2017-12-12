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

char *readLine(FILE *in);

int load(_garcom **garcons, _item **itens, _comanda **comandas, _data *dia);

void readHorario(_horario horario, FILE *in);
void readDay(_data *dia, FILE *s);

typedef struct _data
{
	int  dia, mes, ano; //armazena dia mes e ano
}_data;

typedef struct _horario
{
	int hora, minuto; //armazena horas e minutos
}_horario;

typedef struct _item
{
	char *nome; //armazena o nome do item
	int total;  //armazena o total global de itens vendidos
	double preco; //armazena o preco dos itens
}_item;

typedef struct _venda
{
	_item *item; //aponta para uma lista de itens
	int quantidade; //armazena o total local de itens vendidos
}_venda;

typedef struct _comanda
{
	char mesa[10]; //numero da mesa no formato "MESA #NUM"
	int pessoas;  //armazena o numero de pessoas atendidas
	_horario entrada, saida; //armazena horarios de entrada e saida
	_venda **consumo; //lista de itens consumidos
}_comanda;

typedef struct _garcom
{
	char *nome; //armazena o nome do garcom
	_comanda **comanda; //lista de comandas do garcom
}_garcom;


int main(int argc, char const *argv[])
{
	_data dia; //armazena a data do arquivo
	_garcom **garcons; //lista de garcons
	_item **itens; //lista de itens
	_comanda **comandas; //lista de comandas

	if(!load(garcons, itens, comandas, &dia))
	{
		//se erro no carregamento do arquivo, encerra o programa.
		return 0;
	}
}

int load(_garcom **garcons, _item **itens, _comanda **comandas, _data *dia)
{
	FILE *stream = fopen("consumo.txt", "r"); //abre o arquivo de rotacao diaria
	int ii; //index

	if(!stream)
	{
		//verifica a existencia do arquivo, caso nao exista imprime mensagem de erro e termina a funcao
		fprintf(stdout, "erro ao abrir o arquivo\n");
		return 0;
	}

	readDay(dia, stream); //le o dia


	garcons = malloc(sizeof(_garcom*)*MAXARRAY); //aloca maxima possivel quantidade de garcons
	comandas = malloc(sizeof(_comanda*)*MAXARRAY);//aloca maxima possivel quantidade de comandas
	itens = malloc(sizeof(_item*)*MAXARRAY); //aloca maxima possivel quantidade de itens

	for (ii = 0; ii < feof(stream); ++ii)
	{
		readGarcon(garcons, stream);
		// printf("%s\n", garcons[ii]->nome);
		// readHorario(&garcons->comanda->entrada, stream);
		// readHorario(&garcons->saida, stream);
	}
	return 1;
}

void readDay(_data *dia, FILE *s)
{
	fscanf(s, " %d/%d/%d ", &dia->dia, &dia->mes, &dia->ano);
}

char *readLine(FILE *in)
{
	char *line = malloc(MAXSTRING*sizeof(char)+2); 				//buffer size
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
	char *buffer;
	readLine(in);
}