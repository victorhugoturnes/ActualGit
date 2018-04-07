#include <stdio.h>
#include <stdlib.h>
#include "exercicio.h"

int debugg;

Lista* copyList(Lista* l);

int main(int argc, char const *argv[])
{
	Lista *list = NULL, *list2 = NULL, *str;
	vazia(list);


	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);


/*
	list = insere(list, 1);
	list = insere(list, 2);
	list = insere(list, 3);
	list = insere(list, 4);
	list2 = insere(list2, 5);
	list2 = insere(list2, 6);
	list2 = insere(list2, 7);
	list2 = insere(list2, 8);
	list2 = insere(list2, 9);
*/
	str = merge(list, list2);
//	merge = inverte(list);


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
	return vazia(l1) ? copyList(l2) : insere(concatena(l1->prox, l2), l1->info);
}

Lista* inverte(Lista* l)
{
	return vazia(l) ? NULL : insereCauda(inverte(l->prox), l->info);
}

Lista* remover(Lista* l, int info)
{
	Lista *aux;
	if(!vazia(l))
	{
		l->prox = remover(l->prox, info);
		if(l->info == info){
			aux = l->prox;
			free(l);
			return aux;
		}
	}
	return l;
}

void imprime(Lista* l)
{
	if(!vazia(l))
	{
		printf("(%d)->",l->info);
		imprime(l->prox);
	}else printf("(!)\n");
}

int vazia(Lista * l)
{
	return l ? 0 : 1;
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
	if(l)
	{
		l->prox = insereCauda(l->prox, info);
		return l;
	}

	Lista *temp = (Lista*)malloc(sizeof(Lista));
	temp->info = info;
	temp->prox = NULL;
	return temp;
}