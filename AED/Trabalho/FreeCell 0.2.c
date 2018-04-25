#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

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
int validate(char *command);
void executeCommand(int control, char *command, _table *game);
void parseCommand(char *str);
_table *load(char const *str[])
{
	//TODO: load game
}

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Portuguese");

	_table *game;
	int control = 1;
	char command[3] = {0};

	game = argc > 1 ? load(argv) : newGame();

	while(control)
	{
		system("cls");
		printTable(game);
		parseCommand(command);
		control = validate(command);
		executeCommand(control, command, game);
		printf("%s\n",command );
		system("pause");
	}

	return 0;
}

int validate(char *command)
{

}

void executeCommand(int control, char *command, _table *game)
{

}

void parseCommand(char *str)
{
	scanf(" %c %c", &str[0], &str[1]);
	fflush(stdin);
}

void printCascades(_node *tracer[])
{

	int i;
	int hasNextLine;

	printf("\n|   ");
	for ( i = hasNextLine = 0; i < MAXCASCADES; ++i)
	{
		if(!tracer[i]) printf("        ");
		else{
			printf("[%s,%s] ", suit[tracer[i]->card->suit], rank[tracer[i]->card->rank]);
			if(tracer[i]->next) hasNextLine++;
			tracer[i] = tracer[i]->next;
		}
	}
	printf("  |");
	if(hasNextLine) printCascades(tracer);
}

_node *invert(_node * node)
{
	int i;
	_node *aux = NULL;

	for (i = 0; node; ++i)
	{
		aux = insertHead(aux, node->card);
		node = node->next;
	}
	return aux;
}

void clear(_node *node)
{
	if(node) clear(node->next);
	free(node);
}

void printBody(_table *game)
{
	_node *tracer[MAXCASCADES];
	int i;

	for (i = 0; i < MAXCASCADES; ++i) tracer[i] = invert(game->cascade[i]->top);

	printCascades(tracer);

	printf("\n|");
	for (i = 0; i < MAXOPEN+MAXFOUNDATION; ++i) printf("        ");
	printf("     |\n|");
	for (i = 0; i < MAXOPEN+MAXFOUNDATION; ++i)printf("_______%d", i+1);
	printf("_____|\n");


	for ( i = 0; i < MAXCASCADES; ++i) clear(tracer[i]);
}

void printTable(_table *game)
{
	if(!game)return (void) printf("invalid game\n");
	printHeader(game);
	printBody(game);
	printf("\n");
}

void printHeader(_table *game)
{
	int i;

	for (i = 0; i < MAXOPEN; ++i) printf("____%c___", 'A' + i );
	printf("______");
	for (i = 0; i < MAXFOUNDATION; ++i) printf("___%c____", 'A'+ MAXOPEN + i );
	printf("\n|");
	for (i = 0; i < MAXOPEN; ++i){
		if(!game->open[i]->top)printf("[--,--] ");
		else{
			int rankValue = game->open[i]->top->card->rank;
			int suitValue = game->open[i]->top->card->suit;
			printf("[%s,%s] ", suit[suitValue], rank[rankValue] );
		}
	}
	printf("     ");
	for (i = 0; i < MAXFOUNDATION; ++i){
		if(!game->foundation[i]->top) printf("[--,--] ");
		else {
			char rankValue = game->foundation[i]->top->card->rank;
			char suitValue = game->foundation[i]->top->card->suit;
			printf("[%s,%s] ", suit[suitValue], rank[rankValue] );
		}
	}

	printf("|\n|");
	for (i = 0; i < MAXOPEN+MAXFOUNDATION; ++i) printf("        ");
	printf("     |");
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

	for ( i = 0; deck->top; ++i) moveNode(deck, game->cascade[i%MAXCASCADES]);

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