#ifndef FONCTION_H
#define FONCTION_H

#include "main.h"
#include "insertionavl.h"
#include "rotationavl.h"

long min(long a, long b);
long max(long a, long b);
void affiche(AVL* a);
void libererAVL(AVL* a);
void lire_donnees_en_bloc(AVL** station);

#endif
