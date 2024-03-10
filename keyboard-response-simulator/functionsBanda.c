/* SERB Razvan-Gabriel -> 311CB */
#include "banda.h"

/* InitializeListBanda:
- functie ce initializeaza o lista conform cerintelor pentru continut banda
- intoarce 1 daca s-a reusit initializarea sau 0 daca nu s-a reusit */
int InitializeListBanda(TListBanda *l) {
    *l = (TListBanda) malloc(sizeof(TCellBanda));
    if (!(*l))
        return 0;
    (*l)->info = '|';
    (*l)->prev = NULL;
    (*l)->next = NULL;
    return 1;
}

/* ExtendListBanda:
- functie ce mareste lista cu inca o celula conform cerintelor pentru continut banda
- intoarce 1 daca s-a reusit marirea sau 0 daca nu s-a reusit */
int ExtendListBanda(TListBanda l) {
    for (l = l; l->next != NULL; l = l->next)
        continue;
    l->next = (TListBanda) malloc(sizeof(TCellBanda));
    if (!(l->next))
        return 0;
    l->next->info = '#';
    l->next->prev = l;
    l->next->next = NULL;
    return 1;
}

/* PrintListBanda:
- functie ce afiseaza continutul unei liste specifice unei benzi */
void PrintListBanda(TListBanda l, FILE *foutput) {
    fprintf(foutput, "list: ");
    for (l = l->next; l != NULL; l = l->next)
        fprintf(foutput, "%c ", l->info);
    fprintf(foutput, "\n");
}

/* DestroyListBanda:
- functie ce distruge o lista specifica benzii */
void DestroyListBanda(TListBanda *l) {
    while (*l != NULL) {
        TListBanda aux = *l;
        *l = (*l)->next;
        free(aux);
    }
    *l = NULL;
}

/* InitializeBanda:
- functie ce initializeaza o banda
- intoarce 1 daca s-a reusit initializarea sau 0 daca nu s-a reusit */
int InitializeBanda(TBanda **b) {
    *b = (TBanda *) malloc(sizeof(TBanda));
    if (!(*b))
        return 0;
    if (!InitializeListBanda(&((*b)->content))) {
        free(*b);
        return 0;
    }
    if (!ExtendListBanda((*b)->content))
        return 0;
    (*b)->pos = (*b)->content->next;
    return 1;
}

/* MOVE_LEFT:
- deplasare deget cu o pozitie la stanga */
void MOVE_LEFT(TBanda *b) {
    if (b->pos->prev->info != '|')
        b->pos = b->pos->prev;
}

/* MOVE_RIGHT:
- deplasare deget cu o pozitie la dreapta */
void MOVE_RIGHT(TBanda *b) {
    if (b->pos->next == NULL)
        if (!ExtendListBanda(b->content))
            return;
    b->pos = b->pos->next;
}

/* MOVE_LEFT_CHAR:
- deplasare deget cu pozitii la stanga pana la intalnirea caracterului c */
void MOVE_LEFT_CHAR(TBanda *b, char c, FILE *foutput) {
    TListBanda initial_pos = b->pos;
    if (b->pos->info == c)
        return;
    while (b->pos->prev->info != '|' && b->pos->prev->info != c)
        b->pos = b->pos->prev;
    if (b->pos->prev->info == '|') {
        fprintf(foutput, "ERROR\n");
        b->pos = initial_pos;
        return;
    }
    b->pos = b->pos->prev;
}

/* MOVE_RIGHT_CHAR:
- deplasare deget cu pozitii la dreapta pana la intalnirea caracterului c */
void MOVE_RIGHT_CHAR(TBanda *b, char c) {
    if (b->pos->info == c)
        return;
    while (b->pos->next != NULL && b->pos->next->info != c)
        b->pos = b->pos->next;
    if (b->pos->next == NULL)
        if (!ExtendListBanda(b->content))
            return;
    b->pos = b->pos->next;
}

/* WRITE:
- actualizeaza caracterul curent in caracterul c */
void WRITE(TBanda *b, char c) {
    b->pos->info = c;
}

/* INSERT_LEFT:
- insereaza caracterul c in stanga pozitiei degetului */
int INSERT_LEFT(TBanda *b, char c, FILE *foutput) {
    if (b->pos->prev->info == '|') {
        fprintf(foutput, "ERROR\n");
        return 1;
    }
    TListBanda aux = (TListBanda) malloc(sizeof(TCellBanda));
    if (!aux)
        return 0;
    aux->info = c;
    b->pos->prev->next = aux;
    aux->prev = b->pos->prev;
    aux->next = b->pos;
    b->pos->prev = aux;
    b->pos = aux;
    return 1;
}

/* INSERT_RIGHT:
- insereaza caracterul c in dreapta pozitiei degetului */
int INSERT_RIGHT(TBanda *b, char c) {
    TListBanda aux = (TListBanda) malloc(sizeof(TCellBanda));
    if (!aux)
        return 0;
    aux->info = c;
    if (b->pos->next != NULL)
        b->pos->next->prev = aux;
    aux->next = b->pos->next;
    aux->prev = b->pos;
    b->pos->next = aux;
    b->pos = aux;
    return 1;
}

/* SHOW_CURRENT:
- determinare caracter de pe pozitia degetului */
void SHOW_CURRENT(TBanda *b, FILE *foutput) {
    fprintf(foutput, "%c\n", b->pos->info);
}

/* SHOW:
- afisare continut banda */
void SHOW(TBanda *b, FILE *foutput) {
    // fprintf(foutput, "banda: ");
    TListBanda l = b->content;
    for (l = l->next; l != NULL; l = l->next)
        if (l == b->pos)
            fprintf(foutput, "|%c|", l->info);
        else
            fprintf(foutput, "%c", l->info);
    fprintf(foutput, "\n");
}

/* DestroyBanda:
- functie ce distruge o banda */
void DestroyBanda(TBanda **b) {
    if (!(*b))
        return;
    DestroyListBanda(&((*b)->content));
    (*b)->pos = NULL;
    free(*b);
    *b = NULL;
}

/* InitializeQueue:
- functie ce initializeaza o coada
- intoarce 1 daca s-a reusit initializarea sau 0 daca nu s-a reusit */
int InitializeQueue(TQueue *queue) {
    *queue = (TQueue) malloc(sizeof(TCellQueue));
    if (!(*queue))
        return 0;
    snprintf((*queue)->info, strlen("SENTINEL") + 1, "%s", "SENTINEL");
    (*queue)->prev = (*queue);
    (*queue)->next = (*queue);
    return 1;
}

/* InsertQueue:
- functie ce insereaza o comanda in coada */
int InsertQueue(TQueue queue, char *info) {
    TQueue aux = (TQueue) malloc(sizeof(TCellQueue));
    if (!(aux))
        return 0;
    snprintf(aux->info, strlen(info) + 1, "%s", info);
    aux->prev = queue->prev;
    aux->next = queue;
    queue->prev = aux;
    aux->prev->next = aux;
    return 1;
}

/* ExtractQueue:
- functie ce extrage o comanda din coada */
int ExtractQueue(TQueue queue, char *info) {
    if (!strcmp(queue->next->info, "SENTINEL"))
        return 0;
    snprintf(info, strlen(queue->next->info) + 1, "%s", queue->next->info);
    TQueue aux = queue->next;
    queue->next = queue->next->next;
    queue->next->prev = queue;
    free(aux);
    return 1;
}

/* PrintQueue:
- functie ce afiseaza continutul din coada */
void PrintQueue(TQueue queue, FILE *foutput) {
    fprintf(foutput, "QUEUE:\n");
    TQueue sentinel = queue;
    for (queue = queue->next; queue != sentinel; queue = queue->next)
        fprintf(foutput, "%s\n", queue->info);
    fprintf(foutput, "\n");
}

/* DestroyQueue:
- functie ce distruge o coada */
void DestroyQueue(TQueue *queue) {
    if (!(*queue))
        return;
    TQueue sentinel = (*queue);
    (*queue) = (*queue)->next;
    while ((*queue) != sentinel) {
        TQueue aux = *queue;
        (*queue) = (*queue)->next;
        free(aux);
    }
    free(sentinel);
    *queue = NULL;
}

/* InitializeStack:
- functie ce initializeaza o stiva
- intoarce 1 daca s-a reusit initializarea sau 0 daca nu s-a reusit */
int InitializeStack(TStack* stack) {
    *stack = (TStack) malloc(sizeof(TCellStack));
    if (!(*stack))
        return 0;
    (*stack)->info = NULL;
    (*stack)->prev = (*stack);
    (*stack)->next = (*stack);
    return 1;
}

/* InsertStack:
- functie ce insereaza o comanda in stiva */
int InsertStack(TStack stack, TListBanda info) {
    TStack aux = (TStack) malloc(sizeof(TCellStack));
    if (!aux)
        return 0;
    aux->info = info;
    aux->prev = stack;
    aux->next = stack->next;
    stack->next = aux;
    aux->next->prev = aux;
    return 1;
}

/* ExtractStack:
- functie ce extrage o banda din stiva */
int ExtractStack(TStack stack, TListBanda *info) {
    if (!(stack->next->info))
        return 0;
    *info = stack->next->info;
    TStack aux = stack->next;
    stack->next = stack->next->next;
    stack->next->prev = stack;
    aux->info = NULL;
    free(aux);
    return 1;
}

/* PrintStack:
- functie ce afiseaza continutul din stiva */
void PrintStack(TStack stack, FILE *foutput) {
    fprintf(foutput, "STACK: ");
    TStack sentinel = stack;
    for (stack = stack->next; stack != sentinel; stack = stack->next)
        fprintf(foutput, "%c ", stack->info->info);
    fprintf(foutput, "\n");
}

/* DestroyStack:
- functie ce distruge o stiva */
void DestroyStack(TStack* stack) {
    if (!(*stack))
        return;
    TStack sentinel = (*stack);
    (*stack) = (*stack)->next;
    while ((*stack) != sentinel) {
        TStack aux = *stack;
        (*stack) = (*stack)->next;
        aux->info = NULL;
        free(aux);
    }
    free(sentinel);
    *stack = NULL;
}
