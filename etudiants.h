#ifndef ETUDIANTS_H
#define ETUDIANTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Etudient
{
    int id;
    char nom[50];
    char prenom[50];
    int note;
    struct Etudient *next;
    struct Etudient *prev;
};
typedef struct Etudient Etudient;

typedef Etudient *ListeEtu;

ListeEtu creationNoeudEtu(int id, const char *nom, const char *prenom, int note);

ListeEtu ajoutEtudientFin(ListeEtu l, int id, char *nom, char *prenom, int note);

ListeEtu suppressionEtudient(ListeEtu l, int id);

ListeEtu modificationEtudient(ListeEtu l, int id);

void rechercheEtudient(ListeEtu l, int id);

void echangeEtu(char *a, char *b);

void trieEtudient(ListeEtu l);

void afficherEtudient(ListeEtu l);

#endif
