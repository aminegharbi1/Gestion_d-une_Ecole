#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "laureats.h"
#include "etudiants.h"
#include "profs.h"
#include "services.h"

MYSQL *conn = NULL;
MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;

const char *server = "localhost";
const char *user = "root";
const char *password = "        ";
const char *database = "mohamed";

ListeEmployes Employes(ListeEmployes listeEmp);
ListeLaureats laureats(ListeLaureats listeLau);
ListeEtu etudient(ListeEtu listeEtu);
ListeProfs profs(ListeProfs listeProf);
void DataBaseEtudients();
void chargerEtudientsDB(ListeEtu listeEtu);
void DataBaseProfs();
void chargerProfsDB(ListeProfs listeProf);
void DataBaseLaureats();
void chargerLaureatDB(ListeLaureats listeLau);
void DataBaseEmployes();
void chargerEmployesDB(ListeEmployes listeEmp);


int main()
{
    ListeLaureats listeLau = NULL;
    ListeEtu listeEtu = NULL;
    ListeProfs listeProf = NULL;
    ListeEmployes listeEmp = NULL;

    int choix;
    listeLau = chargerLaureats("laureats.txt");
    listeProf = chargerProfs("profs.txt");
    listeEmp = chargerEmployes("services.txt");
    DataBaseEtudients();
    DataBaseProfs();
    DataBaseLaureats();
    DataBaseEmployes();

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\t\t\t\t\t Menu Principale \n\n\n");
        printf("1.Gestion Etudients \n\n\n");
        printf("2.Gestion Profs \n\n\n");
        printf("3.Gestion Laureats  \n\n\n");
        printf("4.Gestion Employes \n\n\n");
        printf("5.Quitter\n\n\n");
        printf("\t\t\t\t\t\tChoix:");
        scanf("%d", &choix);
        system("clear");

        switch (choix)
        {
        case 1:
            listeEtu = etudient(listeEtu);
            chargerEtudientsDB(listeEtu);
            break;
        case 2:
            listeProf = profs(listeProf);
            chargerProfsDB(listeProf);
            break;
        case 3:
            listeLau = laureats(listeLau);
            chargerLaureatDB(listeLau);
            break;
        case 4:
            listeEmp = Employes(listeEmp);
            chargerEmployesDB(listeEmp);

            break;
        case 5:
            break;
        default:
            printf("choix invalide:\n");
        }
    } while (choix != 5);

    sauvegarderServices("services.txt", listeEmp);
    sauvegarderLaureats("laureats.txt", listeLau);
    sauvegarderProfs("profs.txt", listeProf);

    ListeEtu tmpEtu;
    while (listeEtu != NULL)
    {
        tmpEtu = listeEtu;
        listeEtu = listeEtu->next;
        free(tmpEtu);
    }
    ListeProfs tmpProf;
    while (listeProf != NULL)
    {
        tmpProf = listeProf;
        listeProf = listeProf->next;
        free(tmpProf);
    }

    ListeLaureats tmpLau;
    while (listeLau != NULL)
    {
        tmpLau = listeLau;
        listeLau = listeLau->next;
        free(tmpLau);
    }
    ListeEmployes tmpEmp;
    while (listeEmp != NULL)
    {
        tmpEmp = listeEmp;
        listeEmp = listeEmp->next;
        free(tmpEmp);
    }
    printf("Au revoir:");
    return 0;
}

ListeEmployes Employes(ListeEmployes listeEmp)
{
    int n, choix, idRecherche, anciennete;
    char poste[50];
    do
    {
        printf("\e[1;1H\e[2J");
        printf("\t\t\t\t\t Menu Employes \n\n\n");
        printf("1.Ajout Employes \n\n\n");
        printf("2.Trie poste Employes \n\n\n");
        printf("3.Trie anciennete Employes \n\n\n");
        printf("4.Affichage Employes \n\n\n");
        printf("5.Quitter\n\n\n");
        printf("\t\t\t\t\t\tChoix:");
        scanf("%d", &choix);
        system("clear");

        switch (choix)
        {
        case 1:
            printf("\e[1;1H\e[2J");
            printf("entrez le nombre d'Employes a ajoute :\n");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("Entrez les information d'Employes N°%d :\n\n", i + 1);
                printf("Entrez l'anciennete de l'employe :\n");
                scanf("%d", &anciennete);
                printf("Entrez le poste de l'employe :\n");
                scanf("%s", poste);
                listeEmp = ajoutEmployesFin(listeEmp, anciennete, poste);
            }
            break;
        case 2:
            printf("\e[1;1H\e[2J");
            triePoste(listeEmp);
            printf("\t\t\t\t\t Affichage apres trie Poste:\n");
            afficherServices(listeEmp);
            getchar();
            getchar();
            break;
        case 3:
            printf("\e[1;1H\e[2J");
            trieAnciennete(listeEmp);
            printf("\t\t\t\t\t Affichage apres trie Anciennete:\n");
            afficherServices(listeEmp);
            getchar();
            getchar();

            break;
        case 4:
            printf("\e[1;1H\e[2J");
            printf("\t\t\t\t\t Affichage:\n");
            afficherServices(listeEmp);
            getchar();
            getchar();
            break;
        case 5:
            break;
        default:
            printf("\e[1;1H\e[2J");
            printf("choix invalide:\n");
            getchar();
            getchar();
        }
    } while (choix != 5);
    return listeEmp;
}

ListeLaureats laureats(ListeLaureats listeLau)
{

    int id, promotion, n, choix, idRecherche;
    char filiere[50];
    do
    {
        printf("\e[1;1H\e[2J");
        printf("\t\t\t\t\t Menu Laureats \n\n\n");
        printf("1.Ajout Laureats \n\n\n");
        printf("2.Metre a jour Laureats \n\n\n");
        printf("3.Affichage Laureats \n\n\n");
        printf("4.Quitter\n\n\n");
        printf("\t\t\t\t\t\tChoix:");
        scanf("%d", &choix);
        system("clear");

        switch (choix)
        {
        case 1:
            printf("\e[1;1H\e[2J");
            printf("entrez le nombre de laureat a ajoute :\n");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("Entrez l'id de Laureat N°%d :\n", i + 1);
                scanf("%d", &id);
                printf("Entrez la promotion :\n");
                scanf("%d", &promotion);
                printf("Entrez la filiere :\n");
                scanf("%s", filiere);
                listeLau = ajoutLaureatsFin(listeLau, id, promotion, filiere);
            }
            break;
        case 2:
            printf("\e[1;1H\e[2J");
            printf("entrez l id:\n");
            scanf("%d", &idRecherche);
            mettreAjourLaureats(listeLau, idRecherche);
            break;
        case 3:
            printf("\e[1;1H\e[2J");
            printf("\t\t\t\t\t Affichage:\n");
            afficherLaureats(listeLau);
            getchar();
            getchar();
            break;
        case 4:
            break;
        default:
            printf("\e[1;1H\e[2J");
            printf("choix invalide:\n");
            getchar();
            getchar();
        }
    } while (choix != 4);
    return listeLau;
}
ListeEtu etudient(ListeEtu listeEtu)
{
    int n, choix, id;
    char nom[100], prenom[100];
    float note;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("\t\t\t\t\t Menu Etudient \n\n\n");
        printf("1.Ajout Etudient \n\n\n");
        printf("2.Trie Etudient \n\n\n");
        printf("3.Affichage Etudient \n\n\n");
        printf("4.Quitter \n\n\n");
        printf("\t\t\t\t\t\tChoix:");
        scanf("%d", &choix);
        //system("clear");
        printf("\e[1;1H\e[2J");

        switch (choix)
        {
        case 1:
           // system("clear");
            printf("\e[1;1H\e[2J");
            printf("Entrez le nombre des etudiants à ajouter :\n");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("Entrez l'id de l'etudiant N°%d :\n", i + 1);
                scanf("%d", &id);
                printf("Entrez le nom de l'etudiant :\n");
                scanf("%s", nom);
                printf("Entrez le prenom de l'etudiant :\n");
                scanf("%s", prenom);
                printf("Entrez la note de l'etudiant :\n");
                scanf("%f", &note);
                listeEtu = ajoutEtudientFin(listeEtu, id, nom, prenom, note);
            }
            break;

        case 2:
            //system("clear");
            printf("\e[1;1H\e[2J");
            trieEtudient(listeEtu);
            printf("\t\t\t\t\t Affichage apres trie:\n");
            afficherEtudient(listeEtu);
            getchar();
            getchar();
            break;

        case 3:
           // system("clear");
            //printf("\e[1;1H\e[2J");
            printf("\t\t\t\t\tAffichage:\n");
            afficherEtudient(listeEtu);
            getchar();
            getchar();

            break;
        case 4:
            break;
        default:
            //system("clear");
            printf("\e[1;1H\e[2J");
            printf("Choix invalide:\n");
            getchar();
            getchar();
            break;
        }
    } while (choix != 4);

    return listeEtu;
}

ListeProfs profs(ListeProfs listeProf)
{
    int n, id, experience, choix;
    char nom[50], prenom[50], specialite[50];

    do
    {
        printf("\e[1;1H\e[2J");
        printf("\t\t\t\t\t Menu Profs \n\n\n");
        printf("1.Ajout Profs \n\n\n");
        printf("2.Trie Profs Experience \n\n\n");
        printf("3.Affichage Profs \n\n\n");
        printf("4.Quitter\n\n\n");
        printf("\t\t\t\t\t\tChoix:");
        scanf("%d", &choix);
        system("clear");
        switch (choix)
        {
        case 1:
            printf("\e[1;1H\e[2J");
            printf("entrez le nombre de prof a ajoute :\n");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("Entrez les informations du Prof N°%d :\n", i + 1);
                printf("\nId:");
                scanf("%d", &id);
                printf("\nNom:");
                scanf("%s", nom);
                printf("\nPrenom:");
                scanf("%s", prenom);
                printf("\nSpecialite:");
                scanf("%s", specialite);
                printf("\nExperience:");
                scanf("%d", &experience);
                listeProf = ajoutProfsFin(listeProf, id, nom, prenom, specialite, experience);
            }
            break;
        case 2:
            printf("\e[1;1H\e[2J");
            listeProf = trieProfeExpérience(listeProf);
            printf("\t\t\t\t\tAffichage apres trie:\n");
            afficherProfs(listeProf);
            getchar();
            getchar();
            break;
        case 3:
            printf("\e[1;1H\e[2J");
            printf("\t\t\t\t\tAffichage:\n");
            afficherProfs(listeProf);
            getchar();
            getchar();
            break;
        case 4:
            break;
        default:
            printf("\e[1;1H\e[2J");
            printf("choix invalide:\n");
        }
    } while (choix != 4);
    return listeProf;
}
void DataBaseEtudients()
{
    conn = mysql_init(NULL);

    // Connect to database
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(-1);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    const char *create_table_query =
        "CREATE TABLE IF NOT EXISTS Etudiant ("
        "Id INT AUTO_INCREMENT PRIMARY KEY, "
        "Nom VARCHAR(100) NOT NULL, "
        "Prenom VARCHAR(100) NOT NULL, "
        "Note INT NOT NULL)";

    if (mysql_query(conn, create_table_query))
    {
        fprintf(stderr, "Erreur CREATE TABLE: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    printf("Table Etudients success\n");
}
void chargerEtudientsDB(ListeEtu listeEtu) {
    const char *insertEtu = "INSERT INTO Etudiant (Nom, Prenom, Note) VALUES ('%s', '%s', %d)";
    char query[256];

    while (listeEtu != NULL) {
        sprintf(query, insertEtu, listeEtu->nom, listeEtu->prenom, listeEtu->note);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erreur insertion Etudients: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(-1);
        }

        listeEtu = listeEtu->next;
    }

    printf("Insertion Etudients réussie.\n");
}
void DataBaseProfs()
{
    conn = mysql_init(NULL);

    // Connect to database
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(-1);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    const char *create_table_query =
        "CREATE TABLE IF NOT EXISTS Profs ("
        "Id INT AUTO_INCREMENT PRIMARY KEY, "
        "Nom VARCHAR(100) NOT NULL, "
        "Prenom VARCHAR(100) NOT NULL, "
        "Specialite VARCHAR(100) NOT NULL, "
        "Experience INT NOT NULL)";

    if (mysql_query(conn, create_table_query))
    {
        fprintf(stderr, "Erreur CREATE TABLE: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    printf("Table Profs success\n");
}
void chargerProfsDB(ListeProfs listeProf) {
    const char *insertProfs = "INSERT INTO Profs (Nom, Prenom, Specialite ,Experience) VALUES ('%s', '%s', '%s', %d)";
    char query[256];

    while (listeProf != NULL) {
        sprintf(query, insertProfs, listeProf->nom, listeProf->prenom, listeProf->specialite, listeProf->experience);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erreur insertion Profs: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(-1);
        }

        listeProf = listeProf->next;
    }

    printf("Insertion Profs réussie.\n");
}
void DataBaseLaureats()
{
    conn = mysql_init(NULL);

    // Connect to database
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(-1);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    const char *create_table_query =
        "CREATE TABLE IF NOT EXISTS Laureats ("
        "Id INT AUTO_INCREMENT PRIMARY KEY, "
        "Promotion INT NOT NULL,"
        "Filiere VARCHAR(100) NOT NULL) ";
    

    if (mysql_query(conn, create_table_query))
    {
        fprintf(stderr, "Erreur CREATE TABLE: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    printf("Table Laureats success\n");
}
void chargerLaureatDB(ListeLaureats listeLau) {
    const char *insertLaureats= "INSERT INTO Laureats (promotion, filiere) VALUES (%d, '%s')";
    char query[256];

    while (listeLau != NULL) {
        sprintf(query, insertLaureats, listeLau->promotion, listeLau->filiere);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erreur insertion Laureat: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(-1);
        }

        listeLau = listeLau->next;
    }

    printf("Insertion Laureats réussie.\n");
}
void DataBaseEmployes()
{
    conn = mysql_init(NULL);

    // Connect to database
    if (conn == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(-1);
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    const char *create_table_query =
        "CREATE TABLE IF NOT EXISTS Employes ("
        "Poste VARCHAR(100) NOT NULL ,"
        "Anciennete INT NOT NULL)";
        
        
    

    if (mysql_query(conn, create_table_query))
    {
        fprintf(stderr, "Erreur CREATE TABLE: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(-1);
    }

    printf("Table Employes success\n");
}
void chargerEmployesDB(ListeEmployes listeEmp) {
    const char *insertEmp= "INSERT INTO Employes (Poste, Anciennete) VALUES ('%s', %d)";
    char query[256];

    while (listeEmp != NULL) {
        sprintf(query, insertEmp, listeEmp->poste, listeEmp->anciennete);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Erreur insertion Employes: %s\n", mysql_error(conn));
            mysql_close(conn);
            exit(-1);
        }

        listeEmp = listeEmp->next;
    }

    printf("Insertion Employes réussie.\n");
}