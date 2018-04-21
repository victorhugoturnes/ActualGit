#include <stdio.h>
#include <stdlib.h>

typedef struct no {
int info;
struct no *prox;
} no;

typedef struct {
	struct *no cabeca = 0;
	struct *no cauda = 0;
}Lista;

no* insereCauda(no* l, int info);

no* copyList(no* l);

int main(int argc, char const *argv[])
{
	Lista list, list2, res;

	insere(&list, 1);
	insere(&list, 2);
	insere(&list, 3);
	insere(&list, 4);
	insere(&list, 5);
	insere(&list, 6);
	insere(&list, 7);

	insere(&list2, 1);
	insere(&list2, 2);
	insere(&list2, 3);
	insere(&list2, 4);
	insere(&list2, 5);
	insere(&list2, 6);

//	imprime(list);
//	imprime(list2);
//	str = concatena(list, list2);
	imprime(str);
//	imprime(list2);
//	imprime(str);
	return 0;
}


no* merge(no* l1, no* l2)
{
	return vazia(l1) ? copyList(l2) : insere(merge(l2, l1->prox), l1->info);
}

no* copyList(no* l)
{
	return vazia(l) ? NULL : insere(copyList(l->prox), l->info);
}

no* concatena(no* l1, no* l2)
{
	return vazia(l1) ? copyList(l2) : insere(concatena(l1->prox, l2), l1->info);
}

no* inverte(no* l)
{
	return vazia(l) ? NULL : insereCauda(inverte(l->prox), l->info);
}

no* remover(no* l, int info)
{
	no *aux;
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

void imprime(no* l)
{
	if(!vazia(l))
	{
		printf("(%d)->",l->info);
		imprime(l->prox);
	}else printf("(!)\n");
}

int vazia(no * l)
{
	return l ? 0 : 1;
}

Lista* insere(no* l, int info)
{
	no *temp = (no*)malloc(sizeof(no));
	temp->info = info;
	temp->prox = l;
	return temp;
}

no* insereCauda(no* l, int info)
{
	if(l)
	{
		l->prox = insereCauda(l->prox, info);
		return l;
	}
	return insere(l, info);
}