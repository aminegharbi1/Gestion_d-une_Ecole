#include "services.h"

int sauvegarderServices(const char *fichier, ListeEmployes listeEmp) {
    FILE *file = fopen(fichier, "w");  // Ouvre le fichier en mode écriture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return -1;  // Retourne -1 si le fichier ne peut pas être ouvert
    }

    ListeEmployes current = listeEmp;  // On commence par le premier employé
    while (current != NULL) {  // Tant qu'il y a des employés dans la liste
        // On écrit les informations de l'employé dans le fichier
        //int id, const char *nom, const char *prenom, int note
        fprintf(file, "%d %s \n", current->anciennete, current->poste );
        current = current->next;  // Passe à l'employé suivant
    }

    fclose(file);  // Ferme le fichier après l'écriture
    return 0;  // Retourne 0 si la sauvegarde a réussi
}

ListeEmployes chargerEmployes(const char *fichier) {
    FILE *file = fopen(fichier, "r");  // Ouvre le fichier en mode lecture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return NULL;  // Retourne NULL si le fichier ne peut pas être ouvert
    }

    ListeEmployes listeEmp = NULL;  // Liste vide au début
    int anciennete ;
    char  poste[50];

    // Lecture des données du fichier et création des nœuds
    while (fscanf(file, "%d %49s \n", &anciennete, poste) == 2) {
        // Ajout du professeur à la liste
        listeEmp = ajoutEmployesFin(listeEmp, anciennete, poste );
    }

    fclose(file);  // Ferme le fichier après la lecture
    return listeEmp;
}

ListeEmployes creationNoeudSer(int anciennete, const char *poste)
{
    ListeEmployes l = (ListeEmployes) malloc(sizeof(Employe));
    if (l == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    l->anciennete = anciennete;
    strncpy(l->poste, poste, sizeof(l->poste) - 1);
    l->poste[sizeof(l->poste) - 1] = '\0'; // we can not use it?
    l->next = l->prev = NULL;

    return l;
}
ListeEmployes ajoutEmployesFin(ListeEmployes l,int anciennete, const char *poste)
{
    ListeEmployes tmp = l;
    ListeEmployes nv = creationNoeudSer(anciennete, poste);

    if (l == NULL)
        return nv;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = nv;
    nv->prev = tmp;

    return l;
}
/*ListeEmployes triePoste(ListeEmployes l)
{
    ListeEmployes tmp1 = NULL, tmp2 = NULL, tmp3 = NULL;
    int valEchange,cpt = 0;
    char posteChange[50];
    
    for (tmp1 = tmp3 = l; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {
            if (strcmp(tmp1->poste,"rh") == 0)
            {
                tmp3 = tmp3->next;
                strcpy(posteChange ,tmp1->next->poste);
                strcpy(tmp1->next->poste ,tmp2->poste);
                strcpy(tmp2->poste ,posteChange);
            }
        }
    }

    for (tmp1 = tmp3; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {   
            if (strcmp(tmp2->poste,"th") == 0)     //strlwr
            {
                tmp3 = tmp3->next;
                strcpy(posteChange ,tmp1->next->poste);
                strcpy(tmp1->next->poste ,tmp2->poste);
                strcpy(tmp2->poste ,posteChange);
            }
        }
        tmp1 = tmp1->next;
    }

    for (tmp1 = tmp3; tmp1 != NULL; tmp1 = tmp1->next)
    {
            if (strcmp(tmp1->poste,"sg") == 0)     //strlwr
            {
                tmp3 = tmp3->next;
                strcpy(posteChange ,tmp1->next->poste);
                strcpy(tmp1->next->poste ,tmp2->poste);
                strcpy(tmp2->poste ,posteChange);
            }
    }
    return l;
}*/
void triePoste(ListeEmployes l)
{
    ListeEmployes tmp1 = NULL, tmp2 = NULL;
    char posteChange[50];
    int tempAnciennete;
    for (tmp1 = l; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {
            if (strcmp(tmp1->poste, tmp2->poste) > 0)
            {
                strcpy(posteChange, tmp1->poste);
                strcpy(tmp1->poste, tmp2->poste);
                strcpy(tmp2->poste, posteChange);
                
                tempAnciennete = tmp1->anciennete;
                tmp1->anciennete = tmp2->anciennete;
                tmp2->anciennete = tempAnciennete;
            }
        }
    }
}

void trieAnciennete(ListeEmployes l)
{
    ListeEmployes tmp1 = NULL, tmp2 = NULL;
    int valEchange;
    for (tmp1 = l; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {
            if (tmp1->anciennete > tmp2->anciennete)
            {
                valEchange = tmp1->anciennete;
                tmp1->anciennete = tmp2->anciennete;
                tmp2->anciennete = valEchange;
            }
        }
    }
}
void afficherServices(ListeEmployes l)
{
    while (l != NULL)
    {
        printf(" poste: %s, anciennete: %d\n", l->poste, l->anciennete);
        l = l->next;
    }
}

//Gestion des employés administratifs, tri et recherche par poste ou ancienneté.
