#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct AVL{
    long identifiant;
    long consommation;
    long capacite;
    int eq; //facteur d'équilibre
    struct AVL* fg;
    struct AVL* fd;
}AVL;

#include "insertionavl.h"
#include "rotationavl.h"
#include "fonction.h"
#endif
