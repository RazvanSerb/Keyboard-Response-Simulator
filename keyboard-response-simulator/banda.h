/* SERB Razvan-Gabriel -> 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXI 101

/* *TListBanda: Lista dublu inlantuita simpla cu santinela folosita pentru a retine continutul benzii */
typedef struct cellBanda {
    char info;
    struct cellBanda *prev;
    struct cellBanda *next;
} TCellBanda, *TListBanda;

/* TBanda: Structura folosita pentru a retine informatii despre o banda */
typedef struct {
    TListBanda content;
    TListBanda pos;
} TBanda;

/* *TQueue: Lista dublu inlantuita circulara cu santinela folosita pentru queue */
typedef struct cellQueue {
    char info[MAXI];
    struct cellQueue *prev;
    struct cellQueue *next;
} TCellQueue, *TQueue;

/* *TStack: Lista dublu inlantuita circulara cu santinela folosita pentru stack */
typedef struct cellStack {
    TListBanda info;
    struct cellStack *prev;
    struct cellStack *next;
} TCellStack, *TStack;

int InitializeListBanda(TListBanda* l);
int ExtendListBanda(TListBanda l);
void PrintListBanda(TListBanda l, FILE* foutput);
void DestroyListBanda(TListBanda *l);
int InitializeBanda(TBanda** b);
void MOVE_LEFT(TBanda* b);
void MOVE_RIGHT(TBanda* b);
void MOVE_LEFT_CHAR(TBanda* b, char c, FILE* foutput);
void MOVE_RIGHT_CHAR(TBanda* b, char c);
int INSERT_LEFT(TBanda* b, char c, FILE* foutput);
int INSERT_RIGHT(TBanda* b, char c);
void WRITE(TBanda* b, char c);
void SHOW_CURRENT(TBanda* b, FILE* foutput);
void SHOW(TBanda* b, FILE* foutput);
void DestroyBanda(TBanda** b);
int InitializeQueue(TQueue* queue);
int InsertQueue(TQueue queue, char* info);
int ExtractQueue(TQueue queue, char* info);
void PrintQueue(TQueue queue, FILE* foutput);
void DestroyQueue(TQueue *queue);
int InitializeStack(TStack* stack);
int InsertStack(TStack stack, TListBanda info);
int ExtractStack(TStack stack, TListBanda* info);
void PrintStack(TStack stack, FILE* foutput);
void DestroyStack(TStack* stack);
