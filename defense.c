#include "defense.h"
#include "utilitaire.h"

// Allouer et initialiser un joueur
t_defense * creerDefense()
{
    t_defense *nouv;

    // Allouer
    nouv = (t_defense *)malloc(1*sizeof(t_defense));

    // Initialiser

    nouv->img=load_bitmap_check("slingslot.bmp");

    nouv->tx = nouv->img->w;
    nouv->ty = nouv->img->h;

    nouv->x = SCREEN_W/2;
    nouv->y = 3*SCREEN_H/4;
    nouv->vit = 5;

    nouv->cpttir0 = 0;

    return nouv;
}

// Actualiser joueur (bouger interactivement et tirer...)
void actualiserDefense(t_defense *joueur,t_listeActeurs *la)
{

    // Déplacements instantanés (pas d'inertie)
    // gestion d'un blocage dans une zone écran (moitié gauche)
    if (key[KEY_LEFT])
    {
        joueur->x -= joueur->vit;
        if (joueur->x<0)
            joueur->x=0;
    }

    if (key[KEY_RIGHT])
    {
        joueur->x += joueur->vit;
        if (joueur->x+joueur->tx > SCREEN_W)
            joueur->x=SCREEN_W-joueur->tx;
    }

    if (key[KEY_UP])
    {
        joueur->y -= joueur->vit;
        if (joueur->y<0)
            joueur->y=0;
    }

    if (key[KEY_DOWN])
    {
        joueur->y += joueur->vit;
        if (joueur->y+joueur->ty > SCREEN_H)
            joueur->y=SCREEN_H-joueur->ty;
    }

    // Gestion du tir...

    // incrémenter la tempo des tirs
    joueur->cpttir0++;

    // si le joueur appui sur la gachette et arme ok...
    if (joueur->cpttir0>=10&&key[KEY_SPACE])
    {
        ajouterActeur(la,joueur->x+joueur->tx,joueur->y+joueur->ty/2,0);
        joueur->cpttir0 = 0;
    }

}

// Dessiner joueur sur la bitmap bmp
void dessinerDefense(BITMAP *bmp,t_defense *joueur)
{
    draw_sprite(bmp,joueur->img,joueur->x,joueur->y);
}
