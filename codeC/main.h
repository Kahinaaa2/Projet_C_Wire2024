#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVL{
    long identifiant;
    long consommation;
    long capacite;
    int eq;
    struct AVL* fg;
    struct AVL* fd;
}AVL;

#include "insertionavl.h"
#include "fonction.h"

void lireDonnees(AVL** station);

#endif
