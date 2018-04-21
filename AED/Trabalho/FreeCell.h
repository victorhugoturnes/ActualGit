#ifndef HEADER_FILE
#define HEADER_FILE

#define MAXCARDS 52
#define MAXCASCADES 8
#define MAXOPEN 4
#define MAXFOUNDATION 4
#define MAXRANKS 13


typedef struct card
{
	char suit;
	char rank;
}_card;

typedef struct node
{
	struct card *card;
	struct node *next;
}_node;

typedef struct list
{
	struct node *head;
	struct node *tail;
}_list;

typedef struct table
{
	struct node *open[MAXOPEN];
	struct list *foundation[MAXFOUNDATION];
	struct list *cascade[MAXCASCADES];
}_table;

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void printDeck(_node *deck);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void startNewGame(_table *game);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void load(_table *game, char const *argv[]);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void createShuffledDeck(_list *l);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void insertHead(_card *c, _list *l);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void insertTail(_card *c, _list *l);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
_card *newCard(char suit, char rank);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
int empty(_list *l);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
_node *newNode(_card *c);


//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void printList(_list *deck);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void startTable(_table *game, _list *deck);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void moveNode(_list *from, _list *to);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
_list *newCascade();

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void play(_table *game);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void printGame(_table *game);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
char *toSuit(_node *cardHolder);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
char *toRank(_node *cardHolder);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
void printHeader(_table *game);

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
int printLine(_table *game);

#endif