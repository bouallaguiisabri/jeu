// savegame.c
#include "savegame.h"

void sauvegarder(Person p, Background b, char *nomfichier)
{
    FILE *file = fopen(nomfichier, "wb");
    if (file)
    {
        fwrite(&p, sizeof(Person), 1, file);
        fwrite(&b, sizeof(Background), 1, file);
        fclose(file);
    }
    else
    {
        printf("Erreur lors de la sauvegarde du jeu.\n");
    }
}

void charger(Person *p, Background *b, char *nomfichier)
{
    FILE *file = fopen(nomfichier, "rb");
    if (file)
    {
        fread(p, sizeof(Person), 1, file);
        fread(b, sizeof(Background), 1, file);
        fclose(file);
    }
    else
    {
        printf("Erreur lors du chargement du jeu.\n");
    }
}

