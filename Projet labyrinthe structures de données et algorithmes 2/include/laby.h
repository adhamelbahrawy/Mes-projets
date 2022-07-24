/** @file laby.h
 *  @brief Prototypes des fonctions utiles dans la conception du labyrinthe
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author ELBAHRAWY Adham
 *  @bug Le clacul du total des valeurs des tresors s'effectue d'une manière incorrecte
 */
#ifndef _LABY_H_
#define _LABY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define NDIR 4
/**
 * @enum Dir
 * @brief Constantes des directions
 */
typedef enum { NORD=0, EST, SUD, OUEST } Dir ;
/**
 * @struct noeud
 * @brief Structure d'un noeud deu labyrinthe
 * La structure est composée de 2 tableaux de DIR éléments, le premier contient 
 * les DIR voisins et le deuxième la distance vers ces voisins tel que la distance 
 * au voisin[i] est contenue dans distances[i]. voisins est initialisé à NULL par
 * défaut et distances à 0. Pour chaque direction d,  tresor[d] est un pointeur de float,
 * qui donne l’adresse d’un tableau contenant exactement distances[d] éléments.
 * L'indice d'un élément non nul (un trésor) dans tresors[d] est sa distance au noeud
 * actuel
 */
typedef struct s_noeud
{
    struct s_noeud *voisins[NDIR];
    int distances[NDIR];
    float *tresors[NDIR];
} *noeud;

//Opérations sur les noeuds
/**
 * @fn noeud nouvNoeud();
 * @brief Créaion d'un noeud vide, isolé. On initialise les voisins et les trésors à NULL 
 * @return noeud
*/
noeud nouvNoeud();
/**
 * @fn void passage(noeud n1, noeud n2, Dir d, int dist, float tr[])
 * @pre La taille du tableau tr[] doit exactement valoir dist (un float par mètre)
 * @brief Créaion d'un passage (à sens unique n1->n2 après implantation des trésors) 
 * entre les noeuds n1 et n2. On suppose que les noeuds sont déjà crées, les indices choisis pour 
 * les champs voisins et distances sont celles proposées par le sujet. La première case du tableau
 * correspond au noeud n1 mais il ne contient pas n2
 * @param n1 
 * @param n2 
 * @param d Direction du passage (typedef enum { NORD=0, EST, SUD, OUEST } Dir ;)
 * @param dist Longueur du passage
 * @param tr Tableau statique de float contenant les éventuels trésors en fn de leur ditance au noeud n1 
 */
void passage(noeud n1, noeud n2, Dir d, int dist, float tr[]);
/**
 * @fn taille(noeud n, int *X, int *Y);
 * @brief Calcule la taille d'un labyrinthe à partir d'un noeud donné.
 * La largeur est contenu dans les entiers pointés respectivement par X et Y.
 * La fonction se sert de la fonction intermédire parcoursRel.
 * @param n Noeud courant
 * @param X 
 * @param Y 
 * @return void
*/
void taille(noeud n, int *X, int *Y);
/**
 * @fn void position(noeud n, int *X, int *Y);
 * @brief Calcule la position d'un noeud passé en argument
 * les entiers pointés respectivement par X et Y contiennent l'absscisse et l'ordonnée
 * minimales trouvés par parcoursRel; ces derniers représentent les corrdonnées d'un noeud
 * par rapport au coin bas gauche.
 * @param n Noeud courant
 * @param X 
 * @param Y 
 */
void position(noeud n, int *X, int *Y);
/**
 * @fn int longueur(noeud n)
 * @brief Calcul la longu
 * @param n Noeud de départ
 * @return int 
 */
int longueur(noeud n);

/**
 * @fn float valeurTotalTresors(noeud n)
 * @brief Parcours le labyrinthe à partir d'un noeud n pour renvoyer la somme de toutes
 * les valeurs des trésors rencontrés. Elle passe par la fonction auxilliaire valeurTotalTresorsAux.
 * @param n 
 * @return float 
 */
float valeurTotalTresors(noeud n);
//Autres structures et opérations utiles

//Les listes de coordonées
/**
 * @struct listeCoord
 * @brief Liste chainée d'éléments contenant un noeud et ses 2 corrdonnés relatifs à un point
 * La structure est notemment utile à la fonction parcoursRel
 */
typedef struct s_listeCoord
{
    noeud node;
    int x;
    int y;
    struct s_listeCoord *next;
} *listeCoord;
//Opérations sur les listes de coordonnées
/**
 * @fn listeCoord nouvLc();
 * @brief Renvoie une listeCoord vide (NULL)
 * @return listeCoord 
 */
listeCoord nouvLc();
/**
 * @fn listeCoord adjTLc(listeCoord l, noeud n, int abs, int ord);
 * @brief Ajoute un struct s_listeCoord en tête de la liste l
 * On ajoute un noeud n aux coordonnées relatifs abs et ord
 * @param l 
 * @param n 
 * @param abs 
 * @param ord 
 * @return listeCoord 
 */
listeCoord adjTLc(listeCoord l, noeud n, int abs, int ord);
/**
 * @fn listeCoord rechLc(listeCoord l, int abs, int ord);
 * @brief Rrechrche un noeud dans la liste à partir de sex coordonnées relatifs sans avoir recours aux
 * adresses/références. La fonction renvoie NULL si le noeud n'est pas dans la liste, et l'élément de la
 * liste se référant à lui sinon.
 * @param l 
 * @param abs 
 * @param ord 
 * @return listeCoord 
 */
listeCoord rechLc(listeCoord l, int abs, int ord);
/**
 * @fn listeCoord supKiemeLc(listeCoord l, unsigned int k);
 * @brief Supprime le k-ième élément de la liste l
 * @param l 
 * @param k 
 * @return listeCoord 
 */
listeCoord supKiemeLc(listeCoord l, unsigned int k);
/**
 * @fn void destroyLc(listeCoord l);
 * @brief Détruit/désalloue la liste sans détruire les noeuds, juste les références à eux
 * @param l 
 */
void destroyLc(listeCoord l);
/**
 * @fn listeCoord parcoursRel(noeud n, int x, int y, listeCoord l);
 * @brief Remplit la liste l avec tous les éléments du labyrinthe grâce à un parcours
 * en profondeur de tous les noeuds. Le noeud n est le noeud courant et x et y sont
 * corrdonées relatifs au point de départ, le premier passé en argument.
 * @param n 
 * @param x 
 * @param y 
 * @param l 
 * @return listeCoord 
 */
listeCoord parcoursRel(noeud n, int x, int y, listeCoord l);
//Sélécteurs utiles des listes de coordonnées
/**
 * @fn int xMax(listeCoord l);
 * @brief Renvoie l'abscisse maximale dans la liste l
 * @param l 
 * @return int 
 */
int xMax(listeCoord l);
/**
 * @fn int xMin(listeCoord l);
 * @brief Renvoie l'abscisse minimale dans la liste l
 * @param l 
 * @return int 
 */
int xMin(listeCoord l);
/**
 * @fn int yMax(listeCoord l);
 * @brief Renvoie l'ordonnée maximale dans la liste l
 * @param l 
 * @return int 
 */
int yMax(listeCoord l);
/**
 * @fn int yMin(listeCoord l);
 * @brief Renvoie l'ordonnée minimale dans la liste l
 * @param l 
 * @return int 
 */
int yMin(listeCoord l);

/**
 * @fn float chemTres(noeud n1, noeud n2, listeCoord lt)
 * @brief Renvoie la valeur d'un éventuel trésor sur le passage entre n1 et n2 et ajoute ses coordonnées dans lt
 * mais tout cela est sous conditions que ces derniers n'y soient pas de base
 * @param n1 
 * @param n2 
 * @param lt 
 * @return float 
 */
float chemTres(noeud n1, noeud n2, listeCoord lt);

//Les listes de passages
/**
 * @struct listeP
 * @brief Liste chainée dont 1 élément contient deux noeuds et la diistance entre eux
 */
typedef struct s_listeP
{
    noeud n1;
    noeud n2;
    unsigned int len;
    struct s_listeP *next;
}*listeP;
//Opérations utiles sur les listes de passages
/**
 * @fn listeP nouvLp()
 * @brief Renvoie une liste vide (NULL)
 * @return listeP 
 */
listeP nouvLp();
/**
 * @fn listeP adjTLp(listeP l, noeud node1, noeud node2)
 * @brief Ajoute en tête dans la liste l d'un element de type struct s_listeP.
 * Le champ next du nouvel élément pointe vers l et c'est cet élément qui est renvoyé.
 * @param l 
 * @param node1 
 * @param node2 
 * @return listeP 
 */
listeP adjTLp(listeP l, noeud node1, noeud node2);
/**
 * @fn listeP rechLp(listeP l, noeud node1, noeud node2)
 * @brief Renvoie l'élément de la liste l contenet le passage entre les 2 noeuds (dans 
 * n'importe quel ordre) et NULL si cet element n'existe pas dans la liste.
 * @param l 
 * @param node1 
 * @param node2 
 * @return listeP 
 */
listeP rechLp(listeP l, noeud node1, noeud node2);
/**
 * @fn listeP supKiemeLp(listeP l, unsigned int k)
 * @brief Suppression du k-ième élement de la liste l
 * @param l 
 * @param k 
 * @return listeP 
 */
listeP supKiemeLp(listeP l, unsigned int k);
/**
 * @fn void destroyLp(listeP l)
 * @brief Désalloue la liste l sans détruire les noeuds
 * @param l 
 */
void destroyLp(listeP l);
/**
 * @fn listeP parcoursRelLen
 * @brief Parcours en profondeur de tous les passages du labyrinthe depuis un noeud n
 * et les store dans la liste l
 * @param n 
 * @param l 
 * @return listeP 
 */
listeP parcoursRelLen(noeud n, listeP l);
/**
 * @fn float valeurTotalTresorsAux(noeud n, listeP pv, listeCoord lt)
 * @brief Parcours le labyrinthe à partir d'un noeud n pour renvoyer la somme de toutes
 * les valeurs des trésors rencontrés, les listes pv et lt sont mises à jour constamment 
 * respectivement avec les passages parcourues et les coordonnées des trésors trouvés.
 * @param n 
 * @param pv 
 * @param lt 
 * @return float 
 */
float valeurTotalTresorsAux(noeud n, listeP pv, listeCoord lt);
#endif