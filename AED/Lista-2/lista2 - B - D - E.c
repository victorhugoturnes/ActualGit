#include <stdio.h>
#include <stdlib.h>
#include "exercicio.h"

Lista* insereCauda(Lista* l, int info);
Lista* copyList(Lista* l);
Lista* append(Lista* l1, Lista* l2);
int conta_ocorrencias(Lista* l, int x);
Lista* elimina_repetidos(Lista* l);

int main(int argc, char const *argv[])
{
	Lista *list = NULL, *list2 = NULL, *str;
	vazia(list);

	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 0);
	list = insere(list, 56);
	list = insere(list, 0);

	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);
	list2 = insere(list2, 1);

	//printf("%d\n", conta_ocorrencias(list, 0));
	elimina_repetidos(list);
	imprime(list);
//	imprime(list2);
//	str = concatena(list, list2);
//	imprime(list2);
//	imprime(str);
	return 0;
}

Lista* removerTodos(Lista* l, int info) // AUXILIAR
{
	Lista *aux;
	if(!vazia(l))
	{
		l->prox = removerTodos(l->prox, info);
		if(l->info == info){
			aux = l->prox;
			free(l);
			return aux;
		}
	}
	return l;
}

Lista* elimina_repetidos(Lista* l) // F
{
	if(!vazia(l)) (removerTodos(l->prox, l->info));
}
int conta_ocorrencias(Lista* l, int x) // E
{
	return vazia(l) ? 0 : (x == l->info) + conta_ocorrencias(l->prox, x);
}

Lista* append(Lista* l1, Lista* l2) // D
{
	if(vazia(l1)) return l2;
	return (vazia(l1->prox)) ? l1->prox = l2 : append(l1->prox, l2);
}

Lista* merge(Lista* l1, Lista* l2) // B
{
	return vazia(l1) ? copyList(l2) : insere(merge(l2, l1->prox), l1->info);
}

Lista* copyList(Lista* l) // AUXILIAR
{
	return vazia(l) ? NULL : insere(copyList(l->prox), l->info);
}

Lista* concatena(Lista* l1, Lista* l2) // B
{
	return vazia(l1) ? copyList(l2) : insere(concatena(l1->prox, l2), l1->info);
}

Lista* inverte(Lista* l) // B
{
	return vazia(l) ? NULL : insereCauda(inverte(l->prox), l->info);
}

Lista* remover(Lista* l, int info) // B
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

void imprime(Lista* l) // B
{
	if(!vazia(l))
	{
		printf("(%d)->",l->info);
		imprime(l->prox);
	}else printf("(!)\n");
}

int vazia(Lista * l) // B
{
	return l ? 0 : 1;
}

Lista* insere(Lista* l, int info) // B
{
	Lista *temp = (Lista*)malloc(sizeof(Lista));
	temp->info = info;
	temp->prox = l;
	return temp;
}

Lista* insereCauda(Lista* l, int info) // AUXILIAR
{
	if(l)
	{
		l->prox = insereCauda(l->prox, info);
		return l;
	}
	return insere(l, info);
}