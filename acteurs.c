#include "acteurs.h"
#include "utilitaire.h"

///Les acteurs representent les projectiles
// Allouer et initialiser un acteur
t_acteur * creerActeur(int x,int y,int type)
{
    t_acteur *nouv;

    // Allouer
    nouv=(t_acteur *)malloc(1*sizeof(t_acteur));

    // Initialiser ...

    // ici ce qui est commun aux acteurs
    nouv->x=x;
    nouv->y=y;
    nouv->comportement=0;
    nouv->cptexplo=0; // pas encore explosé mais on initialise par sécurité
    nouv->vivant=1;

    nouv->img=load_bitmap_check("angry_bird.bmp");
    nouv->tx= nouv->img->w;
    nouv->ty= nouv->img->h;
    nouv->dx=3;
    nouv->dy=0;

    return nouv;
}

// Actualiser un acteur (bouger, sortie écran, fin explosion ...)
void actualiserActeur(t_acteur *acteur)
{

    // deplacement
    acteur->x=acteur->x+acteur->dx;
    acteur->y=acteur->y+acteur->dy;

    // si dépasse le bord alors disparait
    if (acteur->x+acteur->tx<0 || acteur->x>SCREEN_W || acteur->y+acteur->ty<0 || acteur->y>SCREEN_H )
        acteur->vivant=0;

    // si en cours d'explosion incrémenter cptexplo
    // et si explose depuis trop longtemps alors disparait
    if (acteur->comportement==1)
    {
        acteur->cptexplo++;
        if (acteur->cptexplo > 7)
            acteur->vivant=0;
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerActeur(BITMAP *bmp,t_acteur *acteur)
{
    // Si pas d'explosion
    if (acteur->comportement==0)
         draw_sprite(bmp,acteur->img,acteur->x,acteur->y);
    // sinon on dessine l'explosion
    // d'un diamètre décroissant et d'une couleur rougissante
    else
        circlefill(bmp,acteur->x+acteur->tx/2,acteur->y+acteur->ty/2,30-4*acteur->cptexplo,makecol(255,255-15*acteur->cptexplo,255-30*acteur->cptexplo));

}

// Un acteur a été touché ou a touché une cible : modifier son état
// ici on indique qu'il passe en comportement 1 (explosion)
// et le vecteur vitesse est divisé en norme (ralentissement)
void destinActeur(t_acteur *acteur)
{
    acteur->dx=0;
    acteur->dy=0;
    acteur->comportement=1;
    acteur->cptexplo=0;
}
