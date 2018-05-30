#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

#include "FreeCell 0.2.h"
void printCard(Card *card);

//debug functions
void printList(Node *n)
{
	if (n)
	{
		printCard(n->card);
		printList(n->next);
	}
	else
		printf("(!)");
}

///TODO FUNCTIONS
Table *load(char const *str);
int validate(Movement *command, Table *game);
void executeCommand(Movement *command);
void parseCommand(Movement *command);
void save(Table *game);
void saveStack(Node *node, FILE *file);

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Portuguese");

	Table *game;
	Movement *command = (Movement *)malloc(sizeof(Movement));

	int control = 1;

	game = argc > 1 ? load(argv[1]) : newGame();

	while (control)
	{
		system("cls");
		printTable(game);
		parseCommand(command);
		control = validate(command, game);
		if (control > 0)
		{
			executeCommand(command);
		}
	}

	return 0;
}

void loadStack(Stack *stack, FILE *file)
{
	int card;
	fread(&card, sizeof(int), 1, file);
	while (card != -1 && !feof(file))
	{
		stack->top = insertHead(stack->top, newCard(card % MAXRANKS, card / MAXRANKS));
		fread(&card, sizeof(int), 1, file);
	}
}

Table *load(char const *str)
{
	Table *game = newTable();
	FILE *file = fopen(str, "rb");
	if (!file)
		return newGame();
	int i;
	for (i = 0; i < MAXOPEN; i++)
	{
		loadStack(game->open[i], file);
	}
	for (i = 0; i < MAXFOUNDATION; i++)
	{
		loadStack(game->foundation[i], file);
	}
	for (i = 0; i < MAXCASCADES; i++)
	{
		loadStack(game->cascade[i], file);
	}
	fclose(file);
	return game;
}

void saveStack(Node *node, FILE *file)
{
	int card = -1;
	if (node)
	{
		saveStack(node->next, file);
		card = node->card->rank + node->card->suit * MAXRANKS;
		fwrite(&card, sizeof(int), 1, file);
	}
}

void save(Table *game)
{
	printf("please enter filename\n");
	char fileName[MAXSTRING];
	scanf("%s", fileName);
	FILE *file = fopen(fileName, "wb+");
	int i, card = -1;
	for (i = 0; i < MAXOPEN; i++)
	{
		saveStack(game->open[i]->top, file);
		fwrite(&card, sizeof(int), 1, file);		
	}
	for (i = 0; i < MAXFOUNDATION; i++)
	{
		saveStack(game->foundation[i]->top, file);
		fwrite(&card, sizeof(int), 1, file);
	}
	for (i = 0; i < MAXCASCADES; i++)
	{
		saveStack(game->cascade[i]->top, file);
		fwrite(&card, sizeof(int), 1, file);
	}
	fclose(file);
}

void executeCommand(Movement *command)
{
	if (!command->from->top)
		return;
	if (command->to->type == 'O' && !command->to->top)
	{
		moveNode(command->from, command->to);
		return;
	}
	if (command->to->type == 'C')
	{
		if (!command->to->top)
		{
			moveNode(command->from, command->to);
			return;
		}
		if (command->from->top->card->suit % 2 != command->to->top->card->suit % 2)
		{
			if (command->from->top->card->rank + 1 == command->to->top->card->rank)
			{
				moveNode(command->from, command->to);
				return;
			}
		}
	}
	if (command->to->type == 'F')
	{
		if (command->from->top->card->rank == 0 && !command->to->top)
		{
			moveNode(command->from, command->to);
			return;
		}
		if (command->from->top->card->suit == command->to->top->card->suit)
		{
			if (command->from->top->card->rank - 1 == command->to->top->card->rank)
			{
				moveNode(command->from, command->to);
			}
		}
	}
}

void printCard(Card *card)
{
	// SetConsoleTextAttribute(hConsole, 28);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	/* Save current attributes */
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	if (card->suit % 2)
	{
		SetConsoleTextAttribute(hConsole, 86);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 88);
	}

	printf("[%s,%s] ", suit[card->suit], rank[card->rank]);

	/* Restore original attributes */
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

int validate(Movement *command, Table *game)
{
	command->from = NULL;
	command->to = NULL;

	if (command->f == 'Q')
	{
		return 0;
	}
	if (command->f == 'S')
	{
		save(game);
		return -1;
	}
	if (command->f >= '1' && command->f < '1' + MAXCASCADES)
	{
		command->from = game->cascade[command->f - '1'];
	}
	if (command->f >= 'A' && command->f < 'A' + MAXOPEN)
	{
		command->from = game->open[command->f - 'A'];
	}

	if (command->t >= '1' && command->t < '1' + MAXCASCADES)
	{
		command->to = game->cascade[command->t - '1'];
	}
	if (command->t >= 'A' && command->t < 'A' + MAXOPEN)
	{
		command->to = game->open[command->t - 'A'];
	}
	if (command->t >= 'A' + MAXOPEN && command->t < 'A' + MAXOPEN + MAXFOUNDATION)
	{
		command->to = game->foundation[command->t - 'A' - MAXOPEN];
	}

	if (!command->from || !command->to)
		return -1;
	return 1;
}

void parseCommand(Movement *command)
{
	scanf(" %c", &command->f);
	command->f = toupper(command->f);
	if (command->f != 'S' && command->f != 'Q')
	{
		scanf(" %c", &command->t);
		command->t = toupper(command->t);
	}
	else
	{
		command->t = '\0';
	}
	fflush(stdin);
}

void printCascades(Node *tracer[])
{
	int i, hasNextLine;
	printf("\n|   ");
	for (i = hasNextLine = 0; i < MAXCASCADES; ++i)
	{
		if (!tracer[i])
			printf("        ");
		else
		{
			printCard(tracer[i]->card);
			if (tracer[i]->next)
				hasNextLine++;
			tracer[i] = tracer[i]->next;
		}
	}
	printf("  |");
	if (hasNextLine)
		printCascades(tracer);
}

Node *invert(Node *node)
{
	int i;
	Node *aux = NULL;
	for (i = 0; node; ++i)
	{
		aux = insertHead(aux, node->card);
		node = node->next;
	}
	return aux;
}

void clear(Node *node)
{
	if (node)
	{
		clear(node->next);
		free(node);
	}
}

void printBody(Table *game)
{
	Node *tracer[MAXCASCADES];
	int i;

	for (i = 0; i < MAXCASCADES; ++i)
		tracer[i] = invert(game->cascade[i]->top);

	printCascades(tracer);

	printf("\n|");
	for (i = 0; i < MAXOPEN + MAXFOUNDATION; ++i)
		printf("        ");
	printf("     |\n|");
	for (i = 0; i < MAXOPEN + MAXFOUNDATION; ++i)
		printf("_______%d", i + 1);
	printf("_____|\n");

	for (i = 0; i < MAXCASCADES; ++i)
		clear(tracer[i]);
}

void printTable(Table *game)
{
	printHeader(game);
	printBody(game);
	printf("\n");
}

void printHeader(Table *game)
{
	int i;

	for (i = 0; i < MAXOPEN; ++i)
		printf("____%c___", 'A' + i);
	printf("______");
	for (i = 0; i < MAXFOUNDATION; ++i)
		printf("___%c____", 'A' + MAXOPEN + i);
	printf("\n|");
	for (i = 0; i < MAXOPEN; ++i)
	{
		if (!game->open[i]->top)
			printf("[--,--] ");
		else
		{
			printCard(game->open[i]->top->card);
		}
	}
	printf("     ");
	for (i = 0; i < MAXFOUNDATION; ++i)
	{
		if (!game->foundation[i]->top)
			printf("[--,--] ");
		else
		{
			printCard(game->foundation[i]->top->card);
		}
	}

	printf("|\n|");
	for (i = 0; i < MAXOPEN + MAXFOUNDATION; ++i)
		printf("        ");
	printf("     |");
}

void moveNode(Stack *from, Stack *to)
{
	if (!from->top)
		return;

	Node *tracer = from->top;
	from->top = from->top->next;

	tracer->next = to->top;
	to->top = tracer;
}

Table *toTable(Stack *deck)
{
	int i;
	Table *game = newTable();

	for (i = 0; deck->top; ++i)
		moveNode(deck, game->cascade[i % MAXCASCADES]);

	return game;
}

Table *newTable()
{
	Table *table = (Table *)malloc(sizeof(Table));
	int i;

	for (i = 0; i < MAXFOUNDATION; ++i)
	{
		table->foundation[i] = (Stack *)malloc(sizeof(Stack));
		table->foundation[i]->type = 'F';
		table->foundation[i]->top = NULL;
	}

	for (i = 0; i < MAXOPEN; ++i)
	{
		table->open[i] = (Stack *)malloc(sizeof(Stack));
		table->open[i]->type = 'O';
		table->open[i]->top = NULL;
	}

	for (i = 0; i < MAXCASCADES; ++i)
	{
		table->cascade[i] = (Stack *)malloc(sizeof(Stack));
		table->cascade[i]->type = 'C';
		table->cascade[i]->top = NULL;
	}
	return table;
}

Table *newGame()
{
	Stack *deck = (Stack *)malloc(sizeof(Stack));
	deck->top = createShuffledDeck();
	Table *game = toTable(deck);
	free(deck);
	return game;
}

void shuffle(Card *cards[])
{
	int i;
	srand(time(NULL));

	for (i = 0; i < MAXCARDS; ++i)
	{
		int temp = i + rand() % (MAXCARDS - i);
		Card *aux = cards[i];
		cards[i] = cards[temp];
		cards[temp] = aux;
	}
}

Node *createShuffledDeck()
{
	int i;
	Node *l = NULL;
	Card *cards[MAXCARDS];

	for (i = 0; i < MAXCARDS; ++i)
		cards[i] = newCard(i % MAXRANKS, i / MAXRANKS);

	shuffle(cards);

	for (i = 0; i < MAXCARDS; ++i)
		l = insertHead(l, cards[i]);
}

Card *newCard(char rank, char suit)
{
	Card *aux = (Card *)malloc(sizeof(Card));
	aux->rank = rank;
	aux->suit = suit;
	return aux;
}

Node *insertHead(Node *l, Card *c)
{
	Node *aux = (Node *)malloc(sizeof(Node));
	aux->card = c;
	aux->next = l;
	return aux;
}