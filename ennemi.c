#include <stdio.h>
#include "ennemi.h"
#include "utilitaire.h"

// Allouer et initialiser un ennemi
t_ennemi * creerEnnemi(int vague)
{
    t_ennemi *nouv;

    // Pour charger la séquence
    int i;
    char nomfichier[256];
    // Allouer
    nouv=(t_ennemi *)malloc(1*sizeof(t_ennemi));

    // charger les images de la séquence d'animation en fonction des vagues
    for (i=0; i<NIMAGE; i++)
    {
        if(vague<4)
            sprintf(nomfichier,"pig%d.bmp",i);

        if((vague>=4)&&(vague<7))
            sprintf(nomfichier,"pig.strong%d.bmp",i);

        if((vague>=7)&&(vague<10))
            sprintf(nomfichier,"pig.king%d.bmp",i);

        nouv->img[i] = load_bitmap_check(nomfichier);
    }

    nouv->x = SCREEN_W;
    nouv->y = 5*(SCREEN_H-nouv->img[0]->h)/6;

    if((vague>=4)&&(vague<7))
    {
        nouv->dx=-0.75;
        nouv->dy=0;
    }
    else
    {
        nouv->dx = -1.25;
        nouv->dy = 0;
    }
    // pour la taille on se base sur la 1ère image de la séquence
    nouv->tx = nouv->img[0]->w;
    nouv->ty = nouv->img[0]->h;

    nouv->imgcourante=0;
    nouv->cptimg=0;
    nouv->tmpimg=15;
    nouv->hp=vague;

    nouv->vivant=1;

    // Retourner ce nouveau ennemi tout frais
    return nouv;
}

// Actualiser un ennemi (bouger, sortie écran ...)
void actualiserEnnemi(t_ennemi *ennemi)
{

    // deplacement
    ennemi->x=ennemi->x+ennemi->dx;
    ennemi->y=ennemi->y+ennemi->dy;

    // si dépasse un bord alors disparait
    if (ennemi->x+ennemi->tx <0 || ennemi->x>SCREEN_W || ennemi->y+ennemi->ty <0 || ennemi->y>SCREEN_H )
        ennemi->vivant=0;

    ennemi->cptimg++;
    if (ennemi->cptimg>=ennemi->tmpimg)
    {
        ennemi->cptimg=0;

        ennemi->imgcourante++;

        // quand l'indice de l'image courante arrive à NIMAGE
        // on recommence la séquence à partir de 0
        if (ennemi->imgcourante>=NIMAGE)
            ennemi->imgcourante=0;
    }
}

// Dessiner un acteur sur la bitmap bmp
void dessinerEnnemi(BITMAP *bmp,t_ennemi *ennemi)
{
    int i;
    for(i=0; i<ennemi->hp; i++)
    {
        circlefill(bmp, ennemi->x + i*ennemi->tx/5 + 4, ennemi->y, 4, makecol(255, 0, 0));
    }
    draw_sprite(bmp,ennemi->img[ennemi->imgcourante],ennemi->x,ennemi->y);
}


//deplacement d'un ennemi
void deplacement(BITMAP *bmp,t_ennemi*ennemi, int vague)
{
    int couldep, rdep, vdep, bdep;
// consultation carte de déplacement qu’on suppose stockée dans flot_ennemi
    couldep = getpixel(bmp, ennemi->x, ennemi->y);
// séparation des composantes et calcul/affectation du vecteur déplacement déduit
    rdep = getr(couldep);
    vdep = getg(couldep);
    bdep = getb(couldep);

    //nouvelles coordonées
    if (( rdep==255 )&&(vdep==0)&&(bdep==0))
    {
        if((vague>=4)&&(vague<7))
            ennemi->dy =-0.75;
        else
            ennemi->dy=-1.25;
        ennemi->dx =0;
    }
    if (( rdep==0 )&&(vdep==255)&&(bdep==0))
    {
         if((vague>=4)&&(vague<7))
            ennemi->dx =-0.75;
        else
            ennemi->dx=-1.25;
        ennemi->dy = 0;
    }
    if (( rdep==0 )&&(vdep==0)&&(bdep==255))
    {
         if((vague>=4)&&(vague<7))
            ennemi->dy =0.75;
        else
            ennemi->dy=1.25;
        ennemi->dx =0;
    }
}

int verification_mort_ennemi(t_ennemi*ennemi)
{
    return ennemi->vivant;
}

void calcul_points(t_ennemi *ennemi,int *pv,int *score)
{
    if(ennemi->x==0)
        *pv=*pv - 1;

    if((ennemi->vivant==0)&&(ennemi->x>0))
        *score=*score + 1;
}
