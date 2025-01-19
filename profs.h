#ifndef PROFS_H
#define PROFS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Profs
{
    int id;
    char nom[50];
    char prenom[50];
    char specialite[50];
    int experience;
    struct Profs *next;
    struct Profs *prev;
};
typedef struct Profs Profs;

typedef Profs *ListeProfs;

ListeProfs chargerProfs(const char *fichier);

int sauvegarderProfs(const char *fichier, ListeProfs listeEmp);

ListeProfs creationNoeudProfs(int id, const char *nom, const char *prenom, const char *specialite ,int experience);

ListeProfs ajoutProfsFin(ListeProfs l, int id, const char *nom, const char *prenom, const char *specialite ,int experience);

ListeProfs suppressionProfs(ListeProfs l, int id);

ListeProfs modificationProfs(ListeProfs l, int id);

void rechercheSpecialiteProfs(ListeProfs l,const char *specialite);

void echange(char *a, char *b);

ListeProfs trieProfeExpérience(ListeProfs l);

void afficherProfs(ListeProfs l);

#endif
