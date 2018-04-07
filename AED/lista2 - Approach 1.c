#include <stdio.h>
#include <stdlib.h>
#include "exercicio.h"

Lista* insereCauda(Lista* l, int info);

Lista* copyList(Lista* l);

int main(int argc, char const *argv[])
{
	Lista *list = NULL, *list2 = NULL, *str;

	list = insereCauda(list, 0);
	list2 = insere(list2, 0);
	list = insereCauda(list, 1);
	list2 = insere(list2, 1);
	list = insereCauda(list, 2);
	list2 = insere(list2, 2);
	list = insereCauda(list, 3);
	list2 = insere(list2, 3);

	remover(list, 1);
	str = concatena(list, list2);

	imprime(list);
	imprime(list2);
	imprime(str);
	return 0;
}


Lista* merge(Lista* l1, Lista* l2)
{
	return vazia(l1) ? copyList(l2) : insere(merge(l2, l1->prox), l1->info);
}

Lista* copyList(Lista* l)
{
	return vazia(l) ? NULL : insere(copyList(l->prox), l->info);
}

Lista* concatena(Lista* l1, Lista* l2)
{
	Lista *aux = l1;
	return aux;
}

Lista* inverte(Lista* l)
{
	Lista *aux = NULL;
	while(!vazia(l))
	{
		aux = insere(aux, l->info);
		l = l->prox;
	}
	return aux;
}

Lista* remover(Lista* l, int info)
{
	Lista *delete, *aux = l, *prev;
	while(!vazia(aux))
	{
		if(aux->info == info){
			delete = aux->prox;
			free(aux);
			prev->prox = delete;
			return l;
		}
		prev = aux;
		aux = aux->prox;
	}
	return l;
}

void imprime(Lista* l)
{
	Lista *aux = l;
	while(!vazia(aux))
	{
		printf("(%d)->",aux->info);
		aux = aux->prox;
	}
	printf("(!)\n");
}

int vazia(Lista * l)
{
	return !l;
}

Lista* insere(Lista* l, int info)
{
	Lista *temp = (Lista*)malloc(sizeof(Lista));
	temp->info = info;
	temp->prox = l;
	return temp;
}

Lista* insereCauda(Lista* l, int info)
{
	Lista *prev = l, *aux = l;
	while(l)
	{
		prev = l;
		l = l->prox;
	}

	Lista *temp = (Lista*)malloc(sizeof(Lista));
	temp->info = info;
	temp->prox = l;

	prev ? (prev->prox = temp) : (aux = temp);
	return aux;
}