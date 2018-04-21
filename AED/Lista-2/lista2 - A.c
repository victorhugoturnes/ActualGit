#include <stdio.h>
#include <stdlib.h>
#include "exercicio.h"

Lista* insereCauda(Lista* l, int info);

Lista* copyList(Lista* l);

int main(int argc, char const *argv[])
{
	Lista *list = NULL, *list2 = NULL, *str;

	list = insere(list, 0);
	list = insere(list, 1);
	list = insere(list, 2);
	list = insere(list, 3);
	list2 = insere(list2, 4);
	list2 = insere(list2, 5);
	list2 = insere(list2, 6);
	list2 = insere(list2, 7);
	list2 = insere(list2, 8);
	list2 = insere(list2, 9);
	list2 = insere(list2, 10);
	list2 = insere(list2, 11);

	str = copyList(list);
//	str = concatena(list, list2);
	str = merge(list, list2);

	imprime(list);
	imprime(list2);
	imprime(str);
	return 0;
}


Lista* merge(Lista* l1, Lista* l2)
{
	Lista *aux = NULL, *start;
	while(!vazia(l2) && !vazia(l1))
	{
		aux = insere(aux, l1->info);
		l1 = l1->prox;

		aux = insere(aux, l2->info);
		l2 = l2->prox;
	}
	start = aux;
	Lista *secondLast = aux;
	while(aux)
	{
		secondLast = aux;
		aux = aux->prox;
	}
	if(!vazia(secondLast)) secondLast->prox  = vazia(l1) ? copyList(l2) : copyList(l1);
	return start;
}

Lista* copyList(Lista* l)
{
	Lista *aux = NULL;
	while(!vazia(l))
	{
		aux = insereCauda(aux, l->info);
		l = l->prox;
	}
	return aux;
}

Lista* concatena(Lista* l1, Lista* l2)
{
	Lista *aux = copyList(l1), *tail, *head;
	head = aux;
	while(aux)
	{
		tail = aux;
		aux = aux->prox;
	}
	tail->prox = copyList(l2);
	return head;
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
	while(!vazia(l))
	{
		printf("(%d)->",l->info);
		l = l->prox;
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
	Lista *prev = l, *first = l;
	while(l)
	{
		prev = l;
		l = l->prox;
	}

	Lista *temp = (Lista*)malloc(sizeof(Lista));
	temp->info = info;
	temp->prox = l;

	prev ? (prev->prox = temp) : (first = temp);
	return first;
}