#include "laureats.h"

int sauvegarderLaureats(const char *fichier, ListeLaureats listeEmp) {
    FILE *file = fopen(fichier, "w");  // Ouvre le fichier en mode écriture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return -1;  // Retourne -1 si le fichier ne peut pas être ouvert
    }

    ListeLaureats current = listeEmp;  // On commence par le premier employé
    while (current != NULL) {  // Tant qu'il y a des employés dans la liste
        // On écrit les informations de l'employé dans le fichier
        //int id, const char *nom, const char *prenom, int note
        fprintf(file, "%d %d %s \n", current->id, current->promotion, current->filiere);
        current = current->next;  // Passe à l'employé suivant
    }

    fclose(file);  // Ferme le fichier après l'écriture
    return 0;  // Retourne 0 si la sauvegarde a réussi
}

ListeLaureats chargerLaureats(const char *fichier) {
    FILE *file = fopen(fichier, "r");  // Ouvre le fichier en mode lecture
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", fichier);
        return NULL;  // Retourne NULL si le fichier ne peut pas être ouvert
    }

    ListeLaureats listeLau = NULL;  // Liste vide au début
    int id ,promotion ;
    char  filiere[50];

    // Lecture des données du fichier et création des nœuds
    while (fscanf(file, "%d %d %49s \n", &id, &promotion, filiere) == 3) {
        // Ajout du professeur à la liste
        listeLau = ajoutLaureatsFin(listeLau, id, promotion, filiere );
    }

    fclose(file);  // Ferme le fichier après la lecture
    return listeLau;
}

ListeLaureats creationNoeudLau(int id, int promotion, const char *filiere)
{
    ListeLaureats l = malloc(sizeof(Laureats));
    if (l == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
    l->id = id;
    l->promotion = promotion;
    strncpy(l->filiere, filiere, sizeof(l->filiere) - 1);
    l->filiere[sizeof(l->filiere) - 1] = '\0'; // we can not use it?
    l->next = l->prev = NULL;

    return l;
}
ListeLaureats ajoutLaureatsFin(ListeLaureats l, int id, int promotion, const char *filiere)
{
    ListeLaureats tmp = l;
    ListeLaureats nv = creationNoeudLau(id,promotion, filiere);

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
void afficherLaureats(ListeLaureats l)
{
    while (l != NULL)
    {
        printf("id: %d, promotion: %d, filiere: %s\n",l->id, l->promotion, l->filiere);
        l = l->next;
    }
}

ListeLaureats mettreAjourLaureats(ListeLaureats l, int id)
{
    if (l == NULL)
    {
        printf("ListeLaureats vide.\n");
        return NULL;
    }

    ListeLaureats temp = l;
    while (temp != NULL)
    {
        if (temp->id == id)
        {

            printf("\n promotion: ");
            scanf("%d",&temp->promotion);
            getchar();
            printf("\nfiliere: ");
            fgets(temp->filiere, sizeof(temp->filiere), stdin);
            temp->filiere[strcspn(temp->filiere, "\n")] = '\0';

            return l;
        }
        temp = temp->next;
    }

    printf("ID non trouvé.\n");
    return l;
}