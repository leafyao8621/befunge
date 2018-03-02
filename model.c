#include <stdlib.h>
#include <stdio.h>
#include "model.h"
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

const char* dbgstr[] = {"RIGHT", "LEFT", "UP", "DOWN"};

struct Data {
    int jmp: 1;
    int str: 1;
    char map[25][81];
};

struct Cursor {
    unsigned int dir: 2;
    int x, y;
};

Data* init_from_file(char* file_name) {
    FILE* fin = fopen(file_name, "r");
    if (!fin) {
        return NULL;
    }
    Data* opt = malloc(sizeof(Data));
    opt->jmp = 0;
    opt->str = 0;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 81; j++) {
            char temp;
            fscanf(fin, "%c", &temp);
            if (temp == 10) {
                for (int k = j; k < 81; opt->map[i][k++] = ' ');
                break;
            } else {
                opt->map[i][j] = temp;
            }
        }
        opt->map[i][80] = 0;
    }
    return opt;
}

int print_map(Data* d) {
    for (int i = 0; i < 25; puts(d->map[i++]));
}

Cursor* malloc_Cursor(void) {
    Cursor* opt = malloc(sizeof(Cursor));
    opt->dir = RIGHT;
    opt->x = opt->y = 0;
    return opt;
}

int move(Cursor* c) {
    if (!c) {
        puts("move nullptr");
        return 1;
    }
    switch (c->dir) {
    case RIGHT:
        c->x++;
        break;
    case LEFT:
        c->x--;
        break;
    case UP:
        c->y--;
        break;
    case DOWN:
        c->y++;
        break;
    }
    return 0;
}

int handle(Data* d, Cursor* c, Stack* s, int dbg) {
    if (dbg)
        printf("execute (%d,%d): %c\nentering dir: %s\n",
               c->x, c->y, d->map[c->y][c->x], dbgstr[c->dir]);
    if (c->x < 0 || c->x > 79 || c->y < 0 || c->y > 24) {
        puts("Out of bound!");
        return 3;
    }
    if (!d || !c) {
        puts("handle nullptr");
        return 1;
    }
    if (d->str) {
        if (d->map[c->y][c->x] != '"') {
            push(s, d->map[c->y][c->x]);
        } else {
            d->str = 0;
        }
        move(c);
        if (dbg) {
            puts("stack:");
            print_Stack(s);
        }
        return 0;
    }
    if (d->jmp) {
        d->jmp = 0;
        move(c);
        if (dbg) {
            puts("stack:");
            print_Stack(s);
        }
        return 0;
    }
    int temp, a, b, ini, v;
    char inc;
    switch (d->map[c->y][c->x]) {
    case '>':
        c->dir = RIGHT;
        break;
    case '^':
        c->dir = UP;
        break;
    case '<':
        c->dir = LEFT;
        break;
    case 'v':
        c->dir = DOWN;
        break;
    case '?':
        c->dir = rand() % 4;
        break;   
    case '_':
        pop(s, &temp);
        c->dir = temp ? LEFT : RIGHT;
        break;
    case '|':
        pop(s, &temp);
        c->dir = temp ? UP : DOWN;
        break;
    case '"':
        d->str = 1;
        break;
    case ':':
        copy_val(s);
        break;
    case '$':
        pop(s, &temp);
        break;
    case '\\':
        swap_val(s);
        break;
    case '@':
        if (dbg)
            puts("");
        return 2;
    case ',':
        pop(s, &temp);
        if (dbg) printf("out: ");
        putchar((char)temp);
        if (dbg) puts("");
        break;
    case '.':
        pop(s, &temp);
        if (dbg) printf("out: ");
        printf("%d", temp);
        if (dbg) puts("");
        break;
    case '+':
        pop(s, &a);
        pop(s, &b);
        push(s, a + b);
        break;
    case '-':
        pop(s, &a);
        pop(s, &b);
        push(s, b - a);
        break;
    case '*':
        pop(s, &a);
        pop(s, &b);
        push(s, a * b);
        break;
    case '/':
        pop(s, &a);
        pop(s, &b);
        push(s, b / a);
        break;
    case '%':
        pop(s, &a);
        pop(s, &b);
        push(s, b % a);
        break;
    case '!':
        pop(s, &temp);
        push(s, !temp);
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        push(s, d->map[c->y][c->x] - '0');
        break;
    case '#':
        d->jmp = 1;
        break;
    case '&':
        if (dbg) printf("in: ");
        scanf("%d", &ini);
        if (dbg) puts("");
        push(s, ini);
        break;
    case '~':
        if (dbg) printf("in: ");
        scanf("%c", &inc);
        if (dbg) puts("");
        push(s, inc);
        break;
    case 'g':
        pop(s, &a);
        pop(s, &b);
        push(s, d->map[a][b]);
        break;
    case 'p':
        pop(s, &a);
        pop(s, &b);
        pop(s, &v);
        d->map[a][b] = v;
        break;
    }
    move(c);
    if (dbg) {
        printf("exiting dir: %s\n", dbgstr[c->dir]);
        puts("stack:");
        print_Stack(s);
        puts("");
    }
    return 0;
}
