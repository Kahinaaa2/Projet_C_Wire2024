#ifndef INSERTIONAVL_H
#define INSERTIONAVL_H

#include "main.h"
#include "rotationavl.h"
#include "fonction.h"

AVL* creerAVL(long nb, long cap, long conso);
AVL* insererAVL(AVL* a, long e, long v, long c, int* h);

#endif
