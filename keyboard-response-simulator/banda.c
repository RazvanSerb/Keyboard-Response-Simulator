/* SERB Razvan-Gabriel -> 311CB */
#include "banda.h"
#define MAXI 101

int main() {
    FILE* finput = fopen("tema1.in", "r");
    FILE* foutput = fopen("tema1.out", "w");
    TBanda* b = NULL, *aux = NULL;
    if (!InitializeBanda(&b))
        exit(-1);
    TQueue EXECUTE = NULL;
    if (!InitializeQueue(&EXECUTE))
        exit(-1);
    TStack UNDO = NULL, REDO = NULL;
    if (!InitializeStack(&UNDO))
        exit(-1);
    if (!InitializeStack(&REDO))
        exit(-1);
    int n = 0; fscanf(finput, "%d", &n);
    char command[MAXI]; fgets(command, MAXI, finput);
    int i = 0;
    for (i = 1; i <= n; i++) {
        fgets(command, MAXI, finput);
        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';
        if (!strcmp(command, "SHOW_CURRENT")) {
            SHOW_CURRENT(b, foutput);
            continue;
        }
        if (!strcmp(command, "SHOW")) {
            SHOW(b, foutput);
            continue;
        }
        if (!strcmp(command, "UNDO")) {
            if (!InsertStack(REDO, b->pos))
                exit(-1);
            ExtractStack(UNDO, &(b->pos));
            continue;
        }
        if (!strcmp(command, "REDO")) {
            if (!InsertStack(UNDO, b->pos))
                exit(-1);
            ExtractStack(REDO, &(b->pos));
            continue;
        }
        if ((!strcmp(command, "EXECUTE")) && ExtractQueue(EXECUTE, command)) {
            if (!strcmp(command, "MOVE_LEFT")) {
                if (!InsertStack(UNDO, b->pos))
                    exit(-1);
                TListBanda initial_pos = b->pos;
                MOVE_LEFT(b);
                if (b->pos == initial_pos)
                    ExtractStack(UNDO, &(b->pos));
            }
            if (!strcmp(command, "MOVE_RIGHT")) {
                if (!InsertStack(UNDO, b->pos))
                    exit(-1);
                MOVE_RIGHT(b);
            }
            if (strstr(command, "MOVE_LEFT_CHAR"))
                MOVE_LEFT_CHAR(b, command[strlen(command) - 1], foutput);
            if (strstr(command, "MOVE_RIGHT_CHAR"))
                MOVE_RIGHT_CHAR(b, command[strlen(command) - 1]);
            if (strstr(command, "WRITE"))
                WRITE(b, command[strlen(command)-1]);
            if ((strstr(command, "INSERT_LEFT")) && (!INSERT_LEFT(b, command[strlen(command) - 1], foutput)))
                exit(-1);
            if ((strstr(command, "INSERT_RIGHT")) && (!INSERT_RIGHT(b, command[strlen(command) - 1])))
                exit(-1);
            continue;
        }
        if (!InsertQueue(EXECUTE, command))
            exit(-1);
    }
    DestroyQueue(&EXECUTE);
    DestroyStack(&REDO);
    DestroyStack(&UNDO);
    DestroyBanda(&b);
    fclose(finput);
    fclose(foutput);
    return 0;
}
