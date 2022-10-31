#include "collision.h"
#include "utilitaire.h"

// Gérer collision (éventuelle) entre un acteur (un tir) et un ennemi
void collisionActeur(t_ennemi *ennemi,t_acteur *acteur)
{
    int vx,vy,d2;

    // si il n'explose déjà pas !
    if ( acteur->comportement==0 )
    {
        // si il est dans la cible alors appeler destinActeur (explosion)

        // calcul du vecteur entre acteur et centre cible
        vx = acteur->x+acteur->tx/2 - (ennemi->x+ennemi->tx/2);
        vy = acteur->y+acteur->ty/2 - (ennemi->y+ennemi->ty/2);

        // calcul distance au carré au centre de la cible (Pythagore)
        // (on reste sur le carré pour éviter de calculer la racine)
        d2 = vx*vx + vy*vy;

        // si dans le disque alors destin...
        if ( d2 < ennemi->tx* ennemi->tx )
        {
            destinActeur(acteur);
            ennemi->hp=ennemi->hp-1;
            if(ennemi->hp==0)
                ennemi->vivant=0;
        }
    }
}

// Gérer les collisions entre les acteurs (tous les tirs) et un ennemi
void collisionListeActeurs(t_listeEnnemis*le,t_listeActeurs *la)
{

    int i;
    int j;
    // regarder pour chaque acteur...
    for (i=0; i<la->max; i++)
    {
        for(j=0; j<le->max; j++)
        {
            if ((la->tab[i]!=NULL)&&(le->tab[j]!=NULL))
                collisionActeur(le->tab[j],la->tab[i]);
        }
    }

}


