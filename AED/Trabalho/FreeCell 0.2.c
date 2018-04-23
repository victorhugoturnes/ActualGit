#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "FreeCell 0.2.h"

//debug functions
void printList(_node *n)
{
	if(n)
	{
		printf("[%d, %d]\n", n->card->suit, n->card->rank);
		printList(n->next);
	}
	else printf("(!)");
}

///TODO FUNCTIONS
_table *load(char const *str[]);
_table *load(char const *str[])
{
	//TODO: load game
}
void printTable(_table *game);

int main(int argc, char const *argv[])
{
	_table *game;

	game = argc > 1 ? load(argv) : newGame();

	printTable(game);

	//TODO gameplay

	return 0;
}

void printHeader(_table *game)
{
	int i;

	for (i = 0; i < MAXOPEN; ++i) printf("___%c____", 'A' + i );
	printf("_____");
	for (i = 0; i < MAXFOUNDATION; ++i) printf("___%c____", 'A'+ MAXOPEN + i );

	printf("\n");

	for (i = 0; i < MAXOPEN; ++i) printf("[--,--] ");
	printf("     ");
	for (i = 0; i < MAXFOUNDATION; ++i) printf("[--,--] ");
}

void printTable(_table *game)
{
	if(!game)return (void) printf("invalid game\n");
	printHeader(game);
}

void moveNode(_stack *from, _stack *to)
{
	if(!from->top) return;

	_node *tracer = from->top;
	from->top = from->top->next;

	tracer->next = to->top;
	to->top = tracer;
}

_table *toTable(_stack *deck)
{
	int i;
	_table *game = newTable();

	for ( i = 0; deck->top; ++i)
	{
		moveNode(deck, game->cascade[i%MAXCASCADES]);
	}
	return game;
}

_table *newTable()
{
	_table *table = (_table*) malloc(sizeof(_table));
	int i;

	for ( i = 0; i < MAXFOUNDATION; ++i)
	{
		table->foundation[i] = (_stack*)malloc(sizeof(_stack));
		table->foundation[i]->top = NULL;
	}

	for ( i = 0; i < MAXOPEN; ++i)
	{
		table->open[i] = (_stack*)malloc(sizeof(_stack));
		table->open[i]->top = NULL;
	}

	for ( i = 0; i < MAXCASCADES; ++i)
	{
		table->cascade[i] = (_stack*)malloc(sizeof(_stack));
		table->cascade[i]->top = NULL;
	}
	return table;
}

_table *newGame()
{
	_stack *deck = (_stack*)malloc(sizeof(_stack));
	deck->top = createShuffledDeck();
	_table *game = toTable(deck);
	free(deck);
	return game;
}

void shuffle(_card *cards[])
{
	int i;
	srand(time(NULL));

	for (i = 0; i < MAXCARDS; ++i)
	{
		int temp = i + rand() % (MAXCARDS-i);
		_card *aux = cards[i];
		cards[i] = cards[temp];
		cards[temp] = aux;
	}
}

_node *createShuffledDeck()
{
	int i;
	_node *l = NULL;
	_card *cards[MAXCARDS];

	for (i = 0; i < MAXCARDS; ++i) cards[i] = newCard(i%MAXRANKS, i/MAXRANKS);

	shuffle(cards);

	for (i = 0; i < MAXCARDS; ++i) l = insertHead(l, cards[i]);
}

_card *newCard(char rank, char suit)
{
	_card *aux = (_card*)malloc(sizeof(_card));
	aux->rank = rank;
	aux->suit = suit;
	return aux;
}

_node *insertHead(_node *l, _card *c)
{
	_node *aux = (_node*)malloc(sizeof(_node));
	aux->card = c;
	aux-> next = l;
	return aux;
}