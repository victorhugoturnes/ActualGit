#include <stdio.h>
#include <stdlib.h>
#include "exercicio.h"

Lista* insereCauda(Lista* l, int info);

Lista* copyList(Lista* l);

int main(int argc, char const *argv[])
{
	Lista *list = NULL, *list2 = NULL, *str;
	vazia(list);


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
		if(l->info == info){
			aux = l->prox;
			free(l);
			return aux;
		}else l->prox = remover(l->prox, info);
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