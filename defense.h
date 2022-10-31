#ifndef DEFENSE_H_INCLUDED
#define DEFENSE_H_INCLUDED

#include "listeActeurs.h"
#include <allegro.h>

// Un élément à déplacement interactif
typedef struct defense
{
    int x,y;     // position
    int tx,ty;   // taille
    int vit;     // vitesse des déplacements (nombre de pixels)
    int cpttir0; // tempo armement 0
    BITMAP *img; // sprite (image chargée)
} t_defense;

// Allouer et initialiser un joueur
t_defense * creerDefense();

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserDefense(t_defense *joueur,t_listeActeurs *la);

// Dessiner joueur sur la bitmap bmp
void dessinerDefense(BITMAP *bmp,t_defense *joueur);


#endif // DEFENSE_H_INCLUDED
