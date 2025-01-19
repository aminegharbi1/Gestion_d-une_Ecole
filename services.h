#ifndef SERVICES_H
#define SERVICES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employes
{
    char poste[50];
    int anciennete;
    struct Employes *next;
    struct Employes *prev;
};
typedef struct Employes Employe;

typedef Employe *ListeEmployes;

ListeEmployes chargerEmployes(const char *fichier);

int sauvegarderServices(const char *fichier, ListeEmployes listeEmp);

ListeEmployes creationNoeudSer(int anciennete, const char *poste);

ListeEmployes ajoutEmployesFin(ListeEmployes l,int anciennete, const char *poste);

void triePoste(ListeEmployes l);

void trieAnciennete(ListeEmployes l);

void afficherServices(ListeEmployes l);
//Gestion des employés administratifs, tri et recherche par poste ou ancienneté.
#endif