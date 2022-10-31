#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED

#define NIMAGE 2
#include <allegro.h>

// chaque ennemi qui se déplace
typedef struct ennemi
{
    // coordonnée (du coin sup. gauche)
    float x, y;

    // vecteur deplacement
    float dx, dy;

    // Gestion de l'enchainement des images de la séquence
    // indice de l'image courante
    int imgcourante;
    // on passe à l'image suivante une fois tous les tmpimg
    int cptimg, tmpimg;

    // Séquence d'animation
    BITMAP *img[NIMAGE];

    //taille des bitmaps
    int tx, ty;

    //points de vie
    int hp;
    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_ennemi;

/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser un ennemi
//   ( à adapter selon besoins )
t_ennemi * creerEnnemi();

// Actualiser un ennemi (bouger ...)
void actualiserEnnemi(t_ennemi *ennemi);

// Dessiner un ennemi sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi);

//deplacement des ennemis
void deplacement(BITMAP *bmp,t_ennemi*ennemi, int vague);

//renvoies la valeur de vivant
int verification_mort_ennemi(t_ennemi*ennemi);

//calcul points et score pour un ennemi
void calcul_points(t_ennemi *ennemi,int *pv,int *score);

#endif // ENNEMI_H_INCLUDED
