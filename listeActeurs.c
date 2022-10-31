#include "listeActeurs.h"
#include "utilitaire.h"

// Allouer et initialiser une liste (vide) de acteurs
t_listeActeurs * creerListeActeurs(int maxacteurs)
{
    t_listeActeurs *nouv;
    int i;

    nouv=(t_listeActeurs *)malloc(1*sizeof(t_listeActeurs));

    nouv->max=maxacteurs;
    nouv->n=0;
    nouv->tab=(t_acteur **)malloc(maxacteurs*sizeof(t_acteur*));

    for (i=0; i<maxacteurs; i++)
        nouv->tab[i]=NULL;

    return nouv;
}

// Retourne un bool�en vrai si il reste de la place
// dans la liste, faux sinon
int libreListeActeurs(t_listeActeurs *la)
{
    return la->n < la->max;
}

// Allouer et ajouter un acteur � la liste
// et retourner l'adresse de ce nouveau acteur
// retourne NULL en cas de probl�me
// ( mais il vaut mieux d'abord v�rifier qu'il
//   y a de la place disponible avant d'appeler )
t_acteur * ajouterActeur(t_listeActeurs *la,int x,int y,int type)
{
    int i;
    t_acteur *acteur;

    // Liste pleine, on alloue rien et on retourne NULL...
    if (la->n >= la->max)
        return NULL;

    // Allouer un acteur initialis�
    acteur=creerActeur(x,y,type);

    // Chercher un emplacement libre
    i=0;
    while (la->tab[i]!=NULL && i<la->max)
        i++;

    // Si on a trouv� ...
    // (normalement oui car on a v�rifi� n<max)
    if (i<la->max)
    {
        // Accrocher le acteur � l'emplacement trouv�
        la->tab[i]=acteur;
        la->n++;
    }
    // Sinon c'est qu'il y a un probl�me de coh�rence
    else
        allegro_message("Anomalie gestion ajouterActeur : liste corrompue");

    return acteur;
}

// Enlever et lib�rer un acteur qui �tait dans la liste en indice i
void enleverActeur(t_listeActeurs *la,int i)
{

    // V�rifier qu'il y a bien un acteur accroch� en indice i
    if (la->tab[i]!=NULL)
    {
        // lib�rer la m�moire du acteur
        free(la->tab[i]);

        // marquer l'emplacement comme libre
        la->tab[i]=NULL;
        la->n--;

    }
}

// G�rer l'�volution de l'ensemble des acteurs
void actualiserListeActeurs(t_listeActeurs *la)
{
    int i;

    // actualiser chaque acteur
    // si un acteur n'est plus vivant, l'enlever de la liste
    for (i=0; i<la->max; i++)
        if (la->tab[i]!=NULL)
        {
            actualiserActeur(la->tab[i]);
            if (!la->tab[i]->vivant)
            {
                enleverActeur(la,i);
            }
        }
}

// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerListeActeurs(BITMAP *bmp,t_listeActeurs *la)
{
    int i;

    for (i=0; i<la->max; i++)
        if (la->tab[i]!=NULL)
            dessinerActeur(bmp,la->tab[i]);

}
