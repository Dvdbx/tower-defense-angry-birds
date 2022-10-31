#include "listeEnnemis.h"
#include "utilitaire.h"

// Allouer et initialiser une liste (vide) de ennemis
t_listeEnnemis * creerListeEnnemis(int maxennemis)
{
    t_listeEnnemis *nouv;
    int i;

    nouv=(t_listeEnnemis *)malloc(1*sizeof(t_listeEnnemis));

    nouv->max=maxennemis;
    nouv->n=0;
    nouv->tab=(t_ennemi **)malloc(maxennemis*sizeof(t_ennemi*));

    for (i=0; i<maxennemis; i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Allouer et ajouter un ennemi � la liste
// et retourner l'adresse de ce nouveau ennemi
// retourne NULL en cas de probl�me
// ( mais il vaut mieux d'abord v�rifier qu'il
//   y a de la place disponible avant d'appeler )
t_ennemi * ajouterEnnemi(t_listeEnnemis *la, int vague)
{
    int i;
    t_ennemi *ennemi;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un ennemi initialis�
    ennemi=creerEnnemi(vague);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouv� ...
    // (normalement oui car on a v�rifi� n<max)
    if (i<la->max)
    {
        // Accrocher le ennemi � l'emplacement trouv�
        la->tab[i]=ennemi;
        la->n++;
    }
    // Sinon c'est qu'il y a un probl�me de coh�rence
    else
        allegro_message("Anomalie gestion ajouterEnnemi : liste corrompue");

    return ennemi;
}

// Enlever et lib�rer un ennemi qui �tait dans la liste en indice i
void enleverEnnemi(t_listeEnnemis *la,int i)
{
    // V�rifier qu'il y a bien un ennemi accroch� en indice i
    if (la->tab[i]!=NULL)
    {
        // lib�rer la m�moire du ennemi
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        //la->n--;
    }
}

// G�rer l'�volution de l'ensemble des ennemis
void actualiserListeEnnemis(t_listeEnnemis *la)
{
    int i;

    // actualiser chaque ennemi
    // si un ennemi n'est plus vivant, l'enlever de la liste
    for (i=0; i<la->max; i++)
        if (la->tab[i]!=NULL)
        {
            actualiserEnnemi(la->tab[i]);
            if (!la->tab[i]->vivant)
            {
                enleverEnnemi(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des ennemis
void dessinerListeEnnemis(BITMAP *bmp,t_listeEnnemis *la)
{
    int i;

    for (i=0; i<la->max; i++)
        if (la->tab[i]!=NULL)
            dessinerEnnemi(bmp,la->tab[i]);

}

//deplacement de l'ensemble des ennemis
void depListeEnnemis(BITMAP *bmp,t_listeEnnemis *la,int vague)
{
    int i;
    for (i=0; i<la->max; i++)
        if (la->tab[i]!=NULL)
            deplacement(bmp,la->tab[i],vague);

}

int verification_fin_vague(t_listeEnnemis *la)
{
    int i;
    int fin_de_vague=0;
    for (i=0; i<la->max; i++)
    {
        if (la->tab[i]!=NULL)
        {
            fin_de_vague=fin_de_vague + verification_mort_ennemi(la->tab[i]);
        }
    }
    return fin_de_vague;
}

void calcul_total_points(BITMAP*bmp,t_listeEnnemis *la, int *pv, int *score)
{
    int i;
    for (i=0; i<la->max; i++)
    {
        if (la->tab[i]!=NULL)
        {
           calcul_points(la->tab[i],pv,score);
        }
    }
}
