#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include "listeActeurs.h"

#include "listeEnnemis.h"

// Gérer collision (éventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur);

// Gérer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_listeEnnemis *ennemi,t_listeActeurs *la);


#endif // COLLISION_H_INCLUDED
