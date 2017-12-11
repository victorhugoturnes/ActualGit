#include <stdio.h>

typedef struct _garcom;
typedef struct _data;
typedef struct _horario;
typedef struct _item;
typedef struct _venda;
typedef struct _comanda;
typedef struct _garcom;

typedef struct _data
{
	int  dia, mes, ano;
}_data;

typedef struct _horario
{
	int hora, minuto, segundo;
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
	int mesa;
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
	_garcom **garcons;
	_itens **itens;
	_comanda **comandas;

	if(!load(garcons, itens, comandas))
	{
		return 0;
	}
}

int load(_garcom **garcons, _itens **itens, _comanda **comandas)
{
	return 0;
}