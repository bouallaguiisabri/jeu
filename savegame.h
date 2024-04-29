// savegame.h
#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <stdio.h>

typedef struct
{
    int x;
    int y;
    int health;
} Person;

typedef struct
{
    int level;
} Background;

void sauvegarder(Person p, Background b, char *nomfichier);
void charger(Person *p, Background *b, char *nomfichier);

#endif

