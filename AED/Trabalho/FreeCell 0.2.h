#ifndef HEADER_FILE
#define HEADER_FILE

#define MAXRANKS 13
#define MAXSUITS 4
#define MAXCARDS MAXSUITS*MAXRANKS

#define MAXCASCADES 8
#define MAXOPEN 4
#define MAXFOUNDATION MAXSUITS

#define MAXSTRING 255

//
// Entrada:
// Retorno:
// Pré-condicao:
// Pós-condicao:
char *rank[MAXRANKS] = {" A", " 2", " 3", " 4",
						" 5", " 6", " 7", " 8",
 						" 9", "10", " J", " Q", " K"};

char *suit[MAXSUITS] = {" S", " H", " C", " D"};

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

typedef struct stack
{
	struct node *top;
}_stack;

typedef struct table
{
	struct stack *open[MAXOPEN];
	struct stack *foundation[MAXFOUNDATION];
	struct stack *cascade[MAXCASCADES];
}_table;

// printa as cascades do jogo atual
// Entrada: array de ponteiros dos nodes iniciais de cada cascade
// Retorno: nenhum
// Pré-condicao: nenhum
// Pós-condicao: nenhum
void printCascades(_node *tracer[]);

// devolve uma copia invertida de uma lista
// Entrada: lista
// Retorno: copia invertida da lista
// Pré-condicao: nenhuma
// Pós-condicao: nenhuma
_node *invert(_node * node);

// elimina uma lista de nodes
// Entrada: uma lista de nodes
// Retorno: nenhum
// Pré-condicao: nenhum
// Pós-condicao: nodes liberados
void clear(_node *node);

// imprime o body ou cascades do jogo na tela
// Entrada: jogo atual
// Retorno: nenhum
// Pré-condicao: nenhum
// Pós-condicao: nenhum
void printBody(_table *game);

// imprime o jogo atual no console
// Entrada: jogo atual
// Retorno: nenhum
// Pré-condicao: nenhum
// Pós-condicao: nenhum
void printTable(_table *game);

// imprime o header no console, sendo o header as open e foundations
// Entrada: jogo atual
// Retorno: nenhum
// Pré-condicao: jogo existe
// Pós-condicao: nenhum
void printHeader(_table *game);

// move um elemeto de um stack para outro
// Entrada: stacks fonte e destino;
// Retorno: nenhum
// Pré-condicao: nenhuma
// Pós-condicao: remove elemento do stack from e adiciona no stack to
// 	se o elemento existe, nenhum se nao existe
void moveNode(_stack *from, _stack *to);

// passa as cartas de um deck completo para uma mesa
// Entrada: deck
// Retorno: mesa com o deck preparado para o jogo
// Pré-condicao: nenhuma
// Pós-condicao: cartas do deck espalhadas uniformente na mesa
_table *toTable(_stack *deck);

// inicializa uma nova _table, incializando todos os ponteiros como NULL
// Entrada: nenhuma
// Retorno: _table iniciada
// Pré-condicao: nenhuma
// Pós-condicao: nova _table com ponteiros para NULL
_table *newTable();

// comeca um novo jogo, carregando a mesa com as cartas em posicao inicial
// Entrada: nenhuma
// Retorno: _table iniciada
// Pré-condicao: nenhuma;
// Pós-condicao: nenhuma;
_table *newGame();

// embaralha uma array de ponteiros para _carta
// Entrada: array a ser embaralhada
// Retorno: nenhum
// Pré-condicao: array de tamanaho MAXCARDS
// Pós-condicao: embaralha os elementos
void shuffle(_card *cards[]);

// gera um novo baralho em ordem aleatoria
// Entrada: deck l a ser adicionado um novo baralho
// Retorno: l modificado
// Pré-condicao: nenhuma
// Pós-condicao: adiciona em ordem aleatoria cartas ao deck l
_node *createShuffledDeck();

// cria uma nova carta
// Entrada: naipe e rank da carta
// Retorno: ponteiro para a nova carta
// Pré-condicao: nenhuma
// Pós-condicao: nenhuma
_card *newCard(char rank, char suit);

//	adiciona um novo elemento no incio da lista
// Entrada: lista atual e infomarmacao do novo elemento
// Retorno: novo inicio da lista
// Pré-condicao: nenhuma
// Pós-condicao: nenhuma
_node *insertHead(_node *l, _card *c);

#endif