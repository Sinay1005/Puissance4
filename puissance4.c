/**
 * \page
 * \brief Voici le programme du puissance 4 réalisé lors du projet SAE1.01 Implémentation
 * \author Yanis PONTHOU 1A2
 * \date Start : 08/11/22 End : 20/11/2022 00:53
 * \version 1.1.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \brief Constante pour définir le pion du prénom1
 */
#define PION_A 'X'

/**
 * \brief Constante pour définir le pion du prénom2
 */
#define PION_B 'O'

/**
 * \brief Constante pour le caracètre inconnue
 */
#define INCONNU ' '

/**
 * \brief Constante pour le caractère vide
 */
#define VIDE ' '

/**
 * \def NBLIG
 * \brief Constante pour définir  le nombre de ligne
 */
#define NBLIG 6

/**
 * \def NBCOL
 * \brief Constante pour définir le nombre de colonne
 */
#define NBCOL 7

/**
 * \brief Constante pour définir la colonne de début qui est celle du milieu
 */
#define COLONNE_DEBUT NBCOL / 2

/**
 * \typedef Un type tableau défini par le nombre de ligne et le nombre de colonne
 */
typedef int grille[NBLIG][NBCOL];

int choisirColonne(grille g, char pion, int colonne); //J'ai mis en prototype car ma fonction jouer est avant ma fonction choisirColonne et TrouverLigne
int trouverLigne(grille g, int colonne);



/* -----------------------------DECLARATION DES PROCEDURES ET FONCTIONS------------------------------------------*/



/**
 * \fn void pinitgrille(grille g)
 * \note Status : Done
 * \brief Procédure qui va servir pour initialisé le tableau en tableau vide
 * \param g : tableau "g" de type grille
 */

void pinitgrille(grille g)
{
    int i, j;
    for(i=0;i < NBLIG;i++)
    {
        for(j=0;j < NBCOL;j++)
        {
            g[i][j] = VIDE;
        }
    }
}



/**
 * \fn void afficher
 * \note Status : Done
 * \brief Affiche la grille
 * \param g : Grille, réprésente la grille de jeu
 * \param pion : Caractère, représente le pion à afficher au-dessus de la grille
 * \param colonne : Entier, représente l'indice de la colonne au-dessus de laquelle le pion doit être affiché
 */
void afficher(grille g, char pion, int colonne){
    int i, j;
    system("clear");

/*-----------Affiche les numéros des colonnes-----------*/
    printf(" 1  2  3  4  5  6  7 \n");

/*-----------Affiche le pion au dessus de la colonne-----------*/
    switch (colonne)
    {
    case 0:
        printf(" %c", pion);
        break;
    case 1:
        printf("    %c\n", pion);
        break;
    case 2:
        printf("       %c\n", pion);
        break;
    case 3:
        printf("          %c\n", pion);
        break;
    case 4:
        printf("             %c\n", pion);
        break;
    case 5:
        printf("                %c\n", pion);
        break;
    case 6:
        printf("                   %c\n", pion);
        break;
    default:
        break;
    }

/*-----------Affiche le fond de grille et si des cases du tableau sont déjà remplis alors il affiche les pions-----------*/
    for(i=0;i < NBLIG;i++){
        printf("\n");
        for(j=0;j < NBCOL;j++){
            if(g[i][j]==VIDE){
                printf(" _ ");
            }
            else{
                printf(" %c ", g[i][j]);
            }
        }
    }

    printf("\n"); // Mise en beauté
    printf("\n");
}



/**
 * \fn booleen grillePleine
 * \note Status : Done
 * \brief Test si toutes les cases de la grille sont occupées
 * \param g : Grille, représente la grille de jeu
 * \result Booléen : Vrai si toutes les cases de la grille sont occupées par les pions, Faux sinon
 */
bool grillePleine(grille g)
{
    int l, c;
    bool resultat = true;
    l = 0;
    c = 0;

    while (l < NBLIG && resultat == true) // Pour parcourire la boucle sans utulisé de for car sinon on parcourirait inutillement toute la grille | inspiré de la recherche séquentielle
    {
        while (c < NBCOL && resultat == true) // Pour parcourire la boucle
        {
            if(g[l][c] == VIDE) // s'il y à une case de vide alors ça veut dire que la grille n'est pas pleine
            {
                resultat = false;
            }
            c = c + 1;
        }
        l = l + 1;
    }
    return resultat;
}



/**
 * \fn void jouer
 * \note Status : Done
 * \brief permet à un joueur de jouer son pion. La procédure fait appel à choisirColonne, afin que le joueur indique la colonne dans laquelle il veut jouer ; puis fait appel à trouverLigne pour définir la case où ajouter le pion.
 * \param g : grille , représente la grille de jeu
 * \param pion : caractère, correspong au pion jouer
 * \param ligne : entier, correspond à la ligne où est tombé le pion
 * \param colonne : eniter, correspond à la colonne où est tombé le pion
 */
void jouer(grille g, char pion, int *ligne, int *colonne)
{

    (*colonne) = choisirColonne(g, pion, COLONNE_DEBUT); // Permet de choisir la colonne

    (*ligne) = trouverLigne(g, *colonne); // Permet de trouver dans la colonne qu'elle ligne est disponible

    g[*ligne][*colonne] = pion; // Place le pion au bonne endroit

}



/**
 * \fn int choisirColonne
 * \note Status : Done
 * \brief Un joueur voit son pion au-dessus de la grille et cette fonction doit lui permettre de "déplacer" son pion d’une colonne vers la gauche (par la touche ‘q’) ou d’une colonne vers la droite (par la touche ‘d’). Après chaque déplacement, la grille est réaffichée. Le joueur peut finalement choisir la colonne où il souhaite faire tomber son pion (par la touche ESPACE).
 * \param g : grille, représente la grille de jeu
 * \param pion : caractère, représente le pion à tester
 * \param colonne : int, colonne de départ
 */
int choisirColonne(grille g, char pion, int colonne)
{
    int col = colonne;
    char deplacement, tmp;


    printf("Pour vous déplacer veuillez appuyer sur : \n q + [entrée]: Pour aller à gauche \n d + [entrée]: pour aller à droite \n[espace] + [entrée]: pour valider \n"); // Message d'instruction
    scanf("%c%c", &deplacement, &tmp); // Lire la touche en faisant attention à la touche [entrée]


    while ((trouverLigne(g, col) == -1) || (deplacement != VIDE)) // Si VIDE = La touche [espace] donc il faut arrêter la boucle Sinon si -1 c'est que la colonne est pleine
    {
        switch (deplacement) //Un switch pour optimiser la chose sachant que l'on à 3 cas " " : placer le jeton "q" : gauche"d" : droite
        {
        case ' ':
            if(trouverLigne(g, col) == -1) // Si -1 la colonne est pleine
            {
                printf("La colonne est malheureusement pleine");
            }
            break;

        case 'd':
            if(col< NBCOL -1)
            {
                col = col +1;
            }
            else{
                printf("Vous êtes au maximum de la grille");
            }
            break;

        case 'q':
            if(col > 0)
            {
                col = col -1;
            }
            else
            {
                printf("Vous êtes au minimum de la grille");
            }
            break;

        default:
                printf("Vous avez surement tapez un mauvais caractère pour rapelle : \n q + [entrée]: Pour aller à gauche \n d + [entrée]: pour aller à droite \n[espace] + [entrée]: pour valider \n");
            break;
        }

        afficher(g, pion, col);
        scanf("%c%c", &deplacement, &tmp);
    }
    return col;
}



/**
 * \fn int trouverLigne
 * \note Status : Done
 * \brief Consiste à trouver la première case non occupée de la colonne. Si la colonne est pleine, la fonction retourne -1.
 * \param g : grille, représente la grille de jeu
 * \param entier : indice de la colonne dans laquelle le pion doit tomber
 * \result entier, indice de la liigne où le pion devra être ajouté ou -1 si la colonne est pleinne.
 */
int trouverLigne(grille g, int colonne){
    int l;
    l = -1; //Initialisation à -1 car si le cas ou la colonne est pleine sinon on aurait mis 0

    while (g[l+1][colonne] == VIDE && l < NBLIG) //Test si la case est vide ou sinon si on a parcouru toute la colonne
    {
        l++;
    }
    return l;
}



/**
 * \fn booleen estVainqueur
 * \brief Indique si le pion situé dans la case repérée par les paramètres ligne et colonne a gagné la partie, c’est-à-dire s’il y a une ligne, une colonne ou une diagonale formée d’au moins 4 de ses pions (la ligne et la colonne passées en paramètres correspondent à la case où le joueur vient de jouer, c’est-à-dire la case à partir de laquelle il faut rechercher 4 pions successifs identiques).
 * \param g : grille, représente la grille de jeu
 * \param ligne : entiers représentant la case à partir de laquelle rechercher une série de 4 successifs identiques
 * \param colonne : entier, entiers représentant la case à partir de laquelle rechercher une série de 4 successifs identiques
 * \result booleen : VRAI s’il y a une telle ligne de 4 à partir de la case indiquée, FAUX sinon.
 */
bool estVainqueur(grille g, int ligne, int colonne)
{
    int i = 0;
    bool res;
    int cpt = 0;
    int alignMax = 0;

    /**
     * Test de la victoire en forme Vertical
     * ligne + i < NBLIG : Si on atteint pas la limite en descendant
     * cpt < 4 : Si le compteur de jeton aligné est inférieur à 4 car sinon ça veut dire que c'est gagné
     * g[ligne+i][colonne] == g[ligne][colonne] Pour vérifié que la case que l'on regarde est bien du même pion que celui de départ sinon ça veut dire que c'est le pion adverse
    */
    while (g[ligne+i][colonne] == g[ligne][colonne] && ligne+i < NBLIG && cpt< 4)
    {
        i++;
        cpt++;
    }
    if(alignMax < cpt){
        alignMax = cpt;
    }
    else{
        alignMax = alignMax;
    }

    /**
     * Test de la victoire en forme Horizontal
    */

    cpt= 0;
    i = 0;

    while (g[ligne][colonne+i] == g[ligne][colonne] && colonne+i < NBCOL && cpt< 4)
    {
        i++;
        cpt++;
    }

    i = 1;
    while (g[ligne][colonne-i] == g[ligne][colonne] && colonne-i >= 0 && cpt< 4)
    {
        i++;
        cpt++;
    }
    if(alignMax < cpt)
    {
        alignMax = cpt;
    }
    else
    {
        alignMax = alignMax;
    }

    /**
     * Test de la victoire diagonale de droite à gauche
    */
    cpt= 0;
    i = 0;
    while (g[ligne-i][colonne-i] == g[ligne][colonne] && colonne-i >= 0 && ligne-i >= 0 && cpt< 4)
    {
        i++;
        cpt++;
    }

    i = 1;
    while (g[ligne+i][colonne+i] == g[ligne][colonne] && colonne+i < NBCOL && ligne+i < NBLIG && cpt< 4)
    {
        i++;
        cpt++;
    }
    if(alignMax < cpt)
    {
        alignMax = cpt;
    }
    else
    {
        alignMax = alignMax;
    }

    /**
     * Test de la victoire diagonale de gauche à droite
    */
    cpt= 0;
    i = 0;
    while (g[ligne-i][colonne+i] == g[ligne][colonne] && colonne+i < NBCOL && ligne-i >= 0 && cpt< 4)
    {
        i++;
        cpt++;
    }

    i = 1;
    while (g[ligne+i][colonne-i] == g[ligne][colonne] && colonne-i >= 0 && ligne+i < NBLIG && cpt< 4)
    {
        i++;
        cpt++;
    }
    if(alignMax < cpt)
    {
        alignMax = cpt;
    }
    else
    {
        alignMax = alignMax;
    }

    // le test final pour savoir quoi renvoyé
    if(alignMax >= 4){
        res = true;
    }
    else{
        res = false;
    }
    return res;
}



/**
 * \fn void finDePartie
 * \note Status : Done
 * \brief Affiche le résultat d’une partie lorsqu’elle est terminée.
 * \param pion : caractère, qui représente le pion gagnant ou bien vide si match nul
 */
void finDePartie(char pion, char nom1[20], char nom2[20]){
    if(pion == VIDE) // Test pour savoir si c'est le cas d'égalité
    {
        printf("Le vainqueur est ...");
        printf("Egalité !!! Personne ne gagne ");
    }
    else if(pion == PION_A){ // Le cas ou c'est le pion_A donc le prénom1
        printf("Victoire du joueur %s avec les pions '%c' Bravo à toi ! \n", nom1, pion);
    }
    else{ // Le cas ou c'est le pion_B donc le prénom2
        printf("Victoire du joueur %s avec les pions '%c' Bravo à toi ! \n", nom2, pion);
    }
}



/**
 * \fn int main
 * \brief Code Principale du puissance 4
 */
int main()
{
    // Déclaration des variables
    char prenom1[20], prenom2[20];
    int ligne, colonne;
    char winner, tmp;
    grille tab;

    // Etape de la saisie des prénoms:
    printf("Le jeu du puissance 4 \n"); //Cf maquette :)
    printf("Prénom du joueur 1 : \n");
    scanf("%s%c", prenom1, &tmp);
    printf("Prénom du joueur 2 : \n");
    scanf("%s%c", prenom2, &tmp);

    //Première étapes d'initialisation
    pinitgrille(tab);
    winner = VIDE;
    afficher(tab, PION_A, COLONNE_DEBUT);

    while (winner==INCONNU && (grillePleine(tab)==false))
    {
        jouer(tab, PION_A, &ligne, &colonne);
        afficher(tab, PION_B, COLONNE_DEBUT);
        if (estVainqueur(tab, ligne, colonne))
        {
            winner = PION_A;
        }
        else if (grillePleine(tab)==false)
        {
            jouer(tab, PION_B, &ligne, &colonne);
            afficher(tab, PION_A, COLONNE_DEBUT);
            if (estVainqueur(tab, ligne, colonne))
            {
                winner = PION_B;
            }
        }
    }
    finDePartie(winner, prenom1, prenom2);
}






