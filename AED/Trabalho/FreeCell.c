#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "FreeCell.h"

int main(int argc, char const *argv[])
{
	_table *game = (_table*)malloc(sizeof(_table));

	if(argc > 1) load(game, argv);
	else startNewGame(game);

	play(game);

//	save(game);

	return 0;
}

void play(_table *game)
{
	int control = 1;
	char *command;

	while(control)
	{
		system("cls");
		printGame(game);
//		control = parse(command);
//		execute(command, control);
//		free(command);
		break;
	}
}

void printGame(_table *game)
{
	int i;
	int control = 1;
	_node *aux[MAXCASCADES];

	printHeader(game);

	for (i = 0; i < MAXCASCADES; ++i) aux[i] = game->cascade[i]->head;

	while(control)
	{
		control = 0;
		for (i = 0; i < MAXCASCADES; ++i)
		{
			if(aux[i]){
				printf("[%s, %s] ", toSuit(aux[i]), toRank(aux[i]));
				aux[i] = aux[i]->next;
			}
			else printf("        ");
			if(i == 3) printf("        ");
			control += (aux[i] > 0);
		}
		printf("\n");
	}
}


void printHeader(_table *game)
{
	int i;
	for (i = 0; i < MAXOPEN; ++i)
	{
		if(game->open[i]) printf("[%s, %s] ", toSuit(game->open[i]), toRank(game->open[i]));
		else printf("[--,--] ");
	}
	printf("	");
	for (i = 0; i < MAXFOUNDATION; ++i)
	{
		if(!empty(game->foundation[i])) printf("[%s, %s] ", toSuit(game->foundation[i]->tail), toRank(game->foundation[i]->tail));
		else printf("[--,--] ");
	}
	printf("\n\n");
}


char *toRank(_node *cardHolder)
{
	switch(cardHolder->card->rank)
	{
		case 0:
			return " A\0";
		case 1:
			return " 1\0";
		case 2:
			return " 2\0";
		case 3:
			return " 3\0";
		case 4:
			return " 4\0";
		case 5:
			return " 5\0";
		case 6:
			return " 6\0";
		case 7:
			return " 7\0";
		case 8:
			return " 8\0";
		case 9:
			return " 9\0";
		case 10:
			return "10\0";
		case 11:
			return " J\0";
		case 12:
			return " Q\0";
		case 13:
			return " K\0";
	}
}

char *toSuit(_node *cardHolder)
{
	switch(cardHolder->card->suit)
	{
		case 0:
			return "s\0";
		case 1:
			return "h\0";
		case 2:
			return "c\0";
		case 3:
			return "d\0";
	}
}

void load(_table *game, char const *argv[])
{

}

void startNewGame(_table *game)
{
	int i;
	_list *deck = newCascade();

	createShuffledDeck(deck);
	startTable(game, deck);

	free(deck);
}


void createShuffledDeck(_list *l)
{
	int i;
	_card *cards[MAXCARDS];

	srand(time(NULL));

	for (i = 0; i < MAXCARDS; ++i)
	{
		cards[i] = newCard(i/MAXRANKS, i%MAXRANKS);
	}

	for (i = 0; i < MAXCARDS; ++i)
	{
		int temp = rand() % MAXCARDS;
		_card *aux = cards[i];
		cards[i] = cards[temp];
		cards[temp] = aux;
	}

	for (i = 0; i < MAXCARDS; ++i)
	{
		rand()%2 ? insertHead(cards[i], l) : insertTail(cards[i], l);
	}
}

void insertHead(_card *c, _list *l)
{
	if(empty(l)) l->head = l->tail = newNode(c);
	else
	{
		_node *aux = l->head;
		l->head = newNode(c);
		l->head->next = aux;
	}
}

void insertTail(_card *c, _list *l)
{
	if(empty(l)) l->head = l->tail = newNode(c);
	else
	{
		_node *aux = l->tail;
		l->tail = newNode(c);
		aux->next = l->tail;
	}
}

_card *newCard(char suit, char rank)
{
	_card *card = (_card*)malloc(sizeof(_card));
	card->suit = suit;
	card->rank = rank;
	return card;
}

_node *newNode(_card *c)
{
	_node *node = (_node*)malloc(sizeof(_node));
	node->card = c;
	node->next = NULL;
	return node;
}
_list *newCascade(){
	_list *deck = (_list*)malloc(sizeof(_list));
	deck->head = deck->tail = NULL;
	return deck;
}

int empty(_list *l)
{
	return !l->head;
}

void printList(_list *deck)
{
	empty(deck) ? printf("deck is currently empty\n") : printDeck(deck->head);
}

void printDeck(_node *deck)
{
	if(!deck) return;
	printDeck(deck->next);
	printf("[%d, %d]\n",deck->card->suit, deck->card->rank );
}

void startTable(_table *game, _list *deck)
{
	int i;
	for (i = 0; i < MAXCASCADES; ++i)
	{
		game->cascade[i] = newCascade();
		if(i<MAXOPEN) game->open[i] = NULL;
		if(i<MAXFOUNDATION)	game->foundation[i] = newCascade();
	}
	for (i = 0; i < MAXCARDS; ++i)
	{
		moveNode(deck, game->cascade[i%MAXCASCADES]);
	}
}

void moveNode(_list *from, _list *to)
{
	_node *temp;
	temp = from->head;
	from->head = from->head->next;
	temp->next = to->head;
	to->head = temp;
	if(!to->tail) to->tail = to->head;
	if(!from->head) from->tail = from->head;
}