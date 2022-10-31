#ifndef LISTEENNEMIS_H_INCLUDED
#define LISTEENNEMIS_H_INCLUDED

#include "ennemi.h"

// Une collection de ennemis
typedef struct listeEnnemis
{
    // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int max;

    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int n;

    // le tableau de pointeurs (alloué dynamiquement)
    t_ennemi **tab;

} t_listeEnnemis;



/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser une liste (vide) de ennemis
t_listeEnnemis * creerListeEnnemis(int maxennemis);

// Allouer et ajouter un ennemi à la liste
// et retourner l'adresse de ce nouveau ennemi
// retourne NULL en cas de problème
t_ennemi * ajouterEnnemi(t_listeEnnemis *la,int vague);

// Enlever et libèrer un ennemi qui était dans la liste en indice i
void enleverEnnemi(t_listeEnnemis *la,int i);

// Gérer l'évolution de l'ensemble des ennemis
void actualiserListeEnnemis(t_listeEnnemis *la);

// Dessiner sur une bitmap l'ensemble des ennemis
void dessinerListeEnnemis(BITMAP *bmp,t_listeEnnemis *la);

//deplacement de toute la vague
void depListeEnnemis(BITMAP *bmp,t_listeEnnemis *la, int vague);

// retourne 0 si la vague est terminee
int verification_fin_vague(t_listeEnnemis *la);

//afficher le score et les points de vie
void calcul_total_points(BITMAP*bmp,t_listeEnnemis *la, int* pv, int* score);

#endif // LISTEENNEMIS_H_INCLUDED
