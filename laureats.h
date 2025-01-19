#ifndef LAUREATS_H
#define LAUREATS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Laureats
{
    int id;
    int promotion;
    char filiere[50];
    struct Laureats *next;
    struct Laureats *prev;
};
typedef struct Laureats Laureats;

typedef Laureats *ListeLaureats;

int sauvegarderLaureats(const char *fichier, ListeLaureats listeEmp);

ListeLaureats chargerLaureats(const char *fichier);

ListeLaureats creationNoeudLau(int id, int promotion, const char *filiere);

ListeLaureats ajoutLaureatsFin(ListeLaureats l, int id, int promotion, const char *filiere);

void afficherLaureats(ListeLaureats l);

ListeLaureats mettreAjourLaureats(ListeLaureats l, int id);

//Les anciens diplômés sont classés par promotion et filière. Le système permet
// d’ajouter de nouveaux lauréats ou de mettre à jour leurs informations.

#endif