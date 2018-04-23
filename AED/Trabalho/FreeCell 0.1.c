#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "FreeCell 0.1.h"

int main(int argc, char const *argv[])
{
	_table *game = (_table*)malloc(sizeof(_table));

	if(argc > 1) load(game, argv);
	else startNewGame(game);

	play(game);

	system("pause");
	system("cls");
//	save(game);

	return 0;
}

void load(_table *game, char const *argv[])
{

}

void save(_table *game)
{

}

void play(_table *game)
{
	int control = 1;
	char *command;

	printGame(game);

	while(control)
	{
//		system("cls");
		printGame(game);
		moveNode(game->cascade[0], game->cascade[1]);
		printf("type \"?\" for help\n");
		//control = parse(&command);
		//printf("%s\n",command, game);
		//execute(command, control, game);
		//free(command);
		system("pause");
	}
}

void printHelp()
{
	system("pause");
}

void validateMove(char *command, _table *game)
{
	_node *from, *to;
	if(strlen(command) != 6) printf("%s is a invalid movement\n", command );
	from = getNode(command[0], command[1], game);
	to = getNode(command[4], command[5], game);
//	system("pause");	
}

_node *getNode(char line, char row, _table *game)
{
	if( row < '0' || row > '8' || line < 'A' || line > 'Z' ) return NULL;
	int i;
	_node *search;

	line -= 'A';
	row -= '0'+1;

	if(!line){
		return row > 4 ? game->foundation[row]->tail : game->open[row];
	}

	search = game->cascade[row]->head;

	for (i = 0; i < line-1; ++i)
	{
		if(!search) return NULL;
		search = search->next;
	}
	return search;
	system("pause");
}


void execute(char *command,int control, _table *game)
{
	switch(control){
		case -1:
			save(game);
			break;
		case 0:
			printf("quitting without saving\n");
			break;
		case 1:
			validateMove(command, game);
			break;
	}
}


int parse(char **line)
{
	int i;

	char *aux = (char*)malloc(sizeof(char)*MAXSTRING);

	scanf("%[^\n]%*c", aux);

	if(strstr(aux, "?")) printHelp();

	for (i = 0; aux[i]; ++i)
	{
		aux[i] = toupper(aux[i]);
	}
	while(strstr(aux, " "))
	{
		for (i = strlen(aux); i>=0; --i)
		{
			if(aux[i] == ' ') aux[i] += aux[i+1] -(aux[i+1] = aux[i]);
		}
	}

	*line = aux;
	if(strstr(aux, "QUIT") || strstr(aux, "EXIT") || !strcmp(aux, "QUIT") || !strcmp(aux, "EXIT"))
		return 0;
	if(strstr(aux, "SAVE")) return -1;
	return 1;
}

void printGame(_table *game)
{
	int i, j;
	int control = 1;
	_node *aux[MAXCASCADES];

	printHeader(game);

	for (i = 0; i < MAXCASCADES; ++i) aux[i] = game->cascade[i]->head;

	for(j=0; control; j++)
	{
		control = 0;
		printf("%c | ", 'B' + j );
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
		printf("|\n");
	}
	printf("  |_________________________________________________________________________|\n");
}


void printHeader(_table *game)
{
	int i;


	printf("   ____1_______2_______3_______4_______________5_______6_______7_______8____\nA | " );

	for (i = 0; i < MAXOPEN; ++i)
	{
		if(game->open[i]) printf("[%s, %s] ", toSuit(game->open[i]), toRank(game->open[i]));
		else printf("[--,--] ");
	}
	printf("        ");
	for (i = 0; i < MAXFOUNDATION; ++i)
	{
		if(!empty(game->foundation[i])) printf("[%s, %s] ", toSuit(game->foundation[i]->tail), toRank(game->foundation[i]->tail));
		else printf("[--,--] ");
	}
	printf("|\n  |                                                                         |\n");
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
			return "S\0";
		case 1:
			return "H\0";
		case 2:
			return "C\0";
		case 3:
			return "D\0";
	}
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