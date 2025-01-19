
#include "etudiants.h"

ListeEtu creationNoeudEtu(int id, const char *nom, const char *prenom, int note)
{
    ListeEtu l = malloc(sizeof(Etudient));
    if (l == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    l->id = id;
    strncpy(l->nom, nom, sizeof(l->nom) - 1);
    l->nom[sizeof(l->nom) - 1] = '\0'; // we can not use it?
    strncpy(l->prenom, prenom, sizeof(l->prenom) - 1);
    l->prenom[sizeof(l->prenom) - 1] = '\0';
    l->note = note;
    l->next = l->prev = NULL;

    return l;
}
ListeEtu ajoutEtudientFin(ListeEtu l,int id, char *nom, char *prenom, int note)
{
    ListeEtu tmp = l;
    ListeEtu nv = creationNoeudEtu(id, nom, prenom, note);

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
ListeEtu suppressionEtudient(ListeEtu l, int id)
{
    if (l == NULL)
    {
        return NULL;
    }

    if (l->id == id)
    {
        l->next->prev = NULL;
        l = l->next;
        return l;
    }
    ListeEtu temp = l;
    while (temp != NULL)
    {
        if (temp->next->id == id)
            break;
        temp = temp->next;
    }
    temp->next->next->prev = temp->next;
    temp->next = temp->next->next;
    free(temp);
    return l;
}
ListeEtu modificationEtudient(ListeEtu l, int id)
{
    if (l == NULL)
    {
        printf("ListeEtu vide.\n");
        return NULL;
    }
    ListeEtu temp = l;
    if (l->id == id)
    {
        printf("\nNom:");
        fgets(temp->nom, 49, stdin);
        temp->nom[strcspn(temp->nom, "\n")] = '\0';
        printf("\nPrenom:");
        fgets(temp->prenom, 49, stdin);
        temp->prenom[strcspn(temp->prenom, "\n")] = '\0';
        printf("\nNote:");
        scanf("%d", &temp->note);
        getchar();
        return l;
    }

    while (temp != NULL)
    {
        if (temp->next->id == id){
            printf("\nNom:");
            fgets(temp->nom, 49, stdin);
            temp->nom[strcspn(temp->nom, "\n")] = '\0';
            printf("\nPrenom:");
            fgets(temp->prenom, 49, stdin);
            temp->prenom[strcspn(temp->prenom, "\n")] = '\0';
            printf("\nNote:");
            scanf("%d", &temp->note);
            getchar();
            return l;
        }

        temp = temp->next;
    }
    printf("ID non trouvé.\n");
    return l;

}
void rechercheEtudient(ListeEtu l, int id)
{
    if (l == NULL)
    {
        printf("ListeEtu vide.\n");
        return;
    }
    if (l->id == id)
    {
        printf("affichage ListeEtu id %d\n", id);
        printf("ID: %d, Nom: %s, Prenom: %s, Note: %d\n", l->id, l->nom, l->prenom, l->note);
        return;
    }

    while (l != NULL)
    {
        if (l->id == id)
            break;
        l = l->next;
    }
    printf("affichage ListeEtu id %d\n", id);
    printf("ID: %d, Nom: %s, Prenom: %s, Note: %d\n", l->id, l->nom, l->prenom, l->note);
}
void echangeEtu(char *a, char *b)
{
    char tmp[50];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

void trieEtudient(ListeEtu l)
{
    ListeEtu tmp1 = NULL, tmp2 = NULL;
    int valEchange;
    for (tmp1 = l; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {
            if (tmp1->id > tmp2->id)
            {
                valEchange = tmp1->id;
                tmp1->id = tmp2->id;
                tmp2->id = valEchange;

                echangeEtu(tmp1->nom, tmp2->nom);
                echangeEtu(tmp1->prenom, tmp2->prenom);

                valEchange = tmp1->note;
                tmp1->note = tmp2->note;
                tmp2->note = valEchange;
            }
        }
    }
}
void afficherEtudient(ListeEtu l)
{
    ListeEtu tmp = l;
    while (tmp != NULL)
    {
        printf("ID: %d, Nom: %s, Prenom: %s, Note: %d\n", tmp->id, tmp->nom, tmp->prenom, tmp->note);
        tmp = tmp->next;
    }
}