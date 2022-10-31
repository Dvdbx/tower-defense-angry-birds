#ifndef LISTEACTEURS_H_INCLUDED
#define LISTEACTEURS_H_INCLUDED

#include "acteurs.h"

// Une collection de acteurs
typedef struct listeActeurs
{
    // nombre maxi d'�l�ments
    // =taille du tableau de pointeurs
    int max;

    // nombre effectif de pointeurs utilis�s
    // (les autres sont � NULL)
    int n;

    // le tableau de pointeurs (allou� dynamiquement)
    t_acteur **tab;

} t_listeActeurs;


/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs);

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la);

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// pour ce projet il faut x y de d�part et type
//   ( � adapter selon besoins )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type);

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i);

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la);

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la);



#endif // LISTEACTEURS_H_INCLUDED
