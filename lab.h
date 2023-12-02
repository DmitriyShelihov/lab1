#ifndef LAB_H
#define LAB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RED           "\x1b[31;2m"
#define YELLOW        "\x1b[33;2m"
#define GREEN         "\x1b[32;2m"
#define BLUE          "\x1b[34;2m"
#define END_OF_COLOUR "\x1b[39;49m"

typedef struct _list
{
    int elem;
    int next;
    int prev;
}LIST;

typedef struct _return_struct
{
    LIST* lst;
    size_t ans_index;
}RET_LIST;

typedef struct _vertex
{
    char elem;
    int value;
}VERTEX;

typedef struct _lab
{
    VERTEX* mas;
    size_t x;
    size_t y;

    int in_x;
    int in_y;
    int out_x;
    int out_y;
}LAB;

LAB lab_read(FILE* source);

void lab_dump(LAB lab);

RET_LIST lab_solve(LAB lab);

#endif
