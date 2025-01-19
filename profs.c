
#include "profs.h"

int sauvegarderProfs(const char *fichier, ListeProfs listeEmp) {
    FILE *file = fopen(fichier, "w");  // Ouvre le fichier en mode écriture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return -1;  // Retourne -1 si le fichier ne peut pas être ouvert
    }

    ListeProfs current = listeEmp;  // On commence par le premier employé
    while (current != NULL) {  // Tant qu'il y a des employés dans la liste
        // On écrit les informations de l'employé dans le fichier
        //int id, const char *nom, const char *prenom, int note
        fprintf(file, "%d %s %s %s %d \n", current->id, current->nom, current->prenom, current->specialite, current->experience);
        current = current->next;  // Passe à l'employé suivant
    }

    fclose(file);  // Ferme le fichier après l'écriture
    return 0;  // Retourne 0 si la sauvegarde a réussi
}

ListeProfs chargerProfs(const char *fichier) {
    FILE *file = fopen(fichier, "r");  // Ouvre le fichier en mode lecture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return NULL;  // Retourne NULL si le fichier ne peut pas être ouvert
    }

    ListeProfs listeEmp = NULL;  // Liste vide au début
    int id, experience;
    char nom[50], prenom[50], specialite[50];

    // Lecture des données du fichier et création des nœuds
    while (fscanf(file, "%d %49s %49s %49s %d\n", &id, nom, prenom, specialite, &experience) == 5) {
        // Ajout du professeur à la liste
        listeEmp = ajoutProfsFin(listeEmp, id, nom, prenom, specialite, experience);
    }

    fclose(file);  // Ferme le fichier après la lecture
    return listeEmp;
}

ListeProfs creationNoeudProfs(int id, const char *nom, const char *prenom, const char *specialite, int experience)
{
    ListeProfs l = (ListeProfs) malloc(sizeof(Profs)); 
    if (l == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    l->id = id;
    strncpy(l->nom, nom, sizeof(l->nom) - 1);
    l->nom[sizeof(l->nom) - 1] = '\0';
    strncpy(l->prenom, prenom, sizeof(l->prenom) - 1);
    l->prenom[sizeof(l->prenom) - 1] = '\0';
    strncpy(l->specialite, specialite, sizeof(l->specialite) - 1);
    l->specialite[sizeof(l->specialite) - 1] = '\0';
    l->experience = experience;

    l->next = l->prev = NULL;

    return l;
}

ListeProfs ajoutProfsFin(ListeProfs l, int id, const char *nom, const char *prenom, const char *specialite, int experience)
{
    ListeProfs tmp = l;
    ListeProfs nv = creationNoeudProfs(id, nom, prenom, specialite, experience);

    if (l == NULL)
        return nv;

    tmp = l;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = nv;
    nv->prev = tmp;

    return l;
}

ListeProfs suppressionProfs(ListeProfs l, int id)
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

    ListeProfs temp = l;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->next->id == id)
            break;
        temp = temp->next;
    }

    if (temp != NULL && temp->next != NULL)
    {
        ListeProfs toDelete = temp->next;
        temp->next = temp->next->next;
        if (temp->next != NULL)
            temp->next->prev = temp;
        free(toDelete);
    }

    return l;
}

// Modify a professor by ID
ListeProfs modificationProfs(ListeProfs l, int id)
{
    if (l == NULL)
    {
        printf("Liste vide.\n");
        return NULL;
    }

    ListeProfs temp = l;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nNom: ");
            fgets(temp->nom, sizeof(temp->nom), stdin);
            temp->nom[strcspn(temp->nom, "\n")] = '\0';

            printf("\nPrenom: ");
            fgets(temp->prenom, sizeof(temp->prenom), stdin);
            temp->prenom[strcspn(temp->prenom, "\n")] = '\0';

            printf("\nSpecialite: ");
            fgets(temp->specialite, sizeof(temp->specialite), stdin);
            temp->specialite[strcspn(temp->specialite, "\n")] = '\0';

            printf("\nNombre d'expérience: ");
            scanf("%d", &temp->experience);
            getchar(); 

            return l;
        }
        temp = temp->next;
    }

    printf("ID non trouvé.\n");
    return l;
}

void rechercheSpecialiteProfs(ListeProfs l, const char *specialite)
{
    if (l == NULL)
    {
        printf("Liste vide.\n");
        return;
    }

    int found = 0;
    while (l != NULL)
    {
        if (strcmp(l->specialite, specialite) == 0)
        {
            printf("Affichage des professeurs spécialisés en %s:\n", specialite);
            printf("ID: %d, Nom: %s, Prenom: %s, Specialite: %s, Experience: %d\n", l->id, l->nom, l->prenom, l->specialite, l->experience);
            found = 1;
        }
        l = l->next;
    }

    if (!found)
    {
        printf("Aucun professeur trouvé pour la spécialité: %s\n", specialite);
    }
}

void echange(char *a, char *b)
{
    char tmp[50];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}

ListeProfs trieProfeExpérience(ListeProfs l)
{
    ListeProfs tmp1 = NULL, tmp2 = NULL;
    int valEchange;
    for (tmp1 = l; tmp1 != NULL; tmp1 = tmp1->next)
    {
        for (tmp2 = tmp1->next; tmp2 != NULL; tmp2 = tmp2->next)
        {
            if (tmp1->experience > tmp2->experience)
            {
                valEchange = tmp1->id;
                tmp1->id = tmp2->id;
                tmp2->id = valEchange;

                echange(tmp1->nom, tmp2->nom);
                echange(tmp1->prenom, tmp2->prenom);
                echange(tmp1->specialite, tmp2->specialite);

                valEchange = tmp1->experience;
                tmp1->experience = tmp2->experience;
                tmp2->experience = valEchange;
            }
        }
    }
    return l;
}

void afficherProfs(ListeProfs l)
{
    while (l != NULL)
    {
        printf("ID: %d, Nom: %s, Prenom: %s, Specialite: %s, Experience: %d\n", l->id, l->nom, l->prenom, l->specialite, l->experience);
        l = l->next;
    }
}
