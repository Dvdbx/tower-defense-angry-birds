#ifndef ACTEURS_H_INCLUDED
#define ACTEURS_H_INCLUDED

#include <allegro.h>

///Les acteurs representent les projectiles

// chaque acteur qui se déplace
typedef struct acteur
{

    // position du coin sup. gauche
    int x,y;

    // vecteur deplacement
    int dx,dy;

    // largeur hauteur
    int tx,ty;

    BITMAP *img;
    // comportement :
    //   0 normal déplacement
    //   1 explosion
    int comportement;
    int cptexplo; // temps depuis l'explosion

    // vivant :
    //   0 mort (doit disparaitre de la liste)
    //   1 vivant
    int vivant;

} t_acteur;

/*********************/
/*     PROTOTYPES    */
/*********************/

// Allouer et initialiser un acteur
// pour ce projet il faut x y de départ et type
//   ( à adapter selon besoins )
t_acteur * creerActeur(int x,int y,int type);

// Actualiser un acteur (bouger ...)
void actualiserActeur(t_acteur *acteur);

// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur);

// Un acteur a été touché ou a touché une cible : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeur(t_acteur *acteur);

#endif // ACTEURS_H_INCLUDED
