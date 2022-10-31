#include <allegro.h>
#include <time.h>

#include "ennemi.h"
#include "listeEnnemis.h"
#include "acteurs.h"
#include "listeActeurs.h"
#include "defense.h"
#include "collision.h"
#include "utilitaire.h"
#include "terrain.h"
///
#define nbennemis 14


/******************************************/
/* PROGRAMME PRINCIPAL                    */
/* initialisation puis boucle d'animation */
/******************************************/

int main()
{
    // Buffer
    BITMAP *page;

    //BITMAPS
    BITMAP *chemin;

    BITMAP *curseur;

    BITMAP*elements;

    BITMAP *decor;
    BITMAP *decor1;
    BITMAP *decor2;
    BITMAP *decor3;

    BITMAP*victoire;
    BITMAP*defaite;

    // La collection des acteurs (les tirs)
    t_listeActeurs *acteurs;

    // Le vaisseau manipulé par le joueur
    t_defense *vaisseau;

    // La collection des ennemis
    t_listeEnnemis *ennemis;

    //condition de sortie
    int fin=0;

    // Proba de création de disque (en %)
    int prob=5;

    //indices de changement de vagues
    int vague=0;

    int pv=10;

    int score=0;

    // pour augmenter dynamiquement le nombre d'ennemis
    int compteur=0;

    // Il y aura du hasard
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();

    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // buffer
    page=create_bitmap(SCREEN_W,SCREEN_H);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    elements=load_bitmap_check("elements_decor.bmp");

    curseur=load_bitmap_check("curseur.bmp");

    decor1=load_bitmap_check("terrain1.bmp");
    decor2=load_bitmap_check("terrain2.bmp");
    decor3=load_bitmap_check("terrain3.bmp");

    victoire=load_bitmap_check("victory.bmp");
    defaite=load_bitmap_check("game_over.bmp");

    chemin=load_bitmap_check("chemin.bmp");

    //on commenc epar le premier decore
    decor=decor1;

    //afficher la souris sur tous les decors
    //show_mouse(screen);

    // créer le vaisseau et la cible
    vaisseau=creerDefense();

    // préparer la liste des ennemis (100 maxi)
    // mais vide initialement
    ennemis=creerListeEnnemis(nbennemis);

    // préparer la liste des acteurs (100 maxi)
    // mais vide initialement
    acteurs=creerListeActeurs(100);

    //on bloquer la premiere vague pour la lancer manuellement
    ennemis->n=nbennemis;

    // BOUCLE DE JEU
    while (!fin)
    {
        // afficher decor
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        ///
        //calculer le score et les points de vie
        calcul_total_points(decor,ennemis,&pv,&score);

        //afficher les pv
        textprintf_ex(page, font, 10, 10, makecol(200, 0, 200), -1, "%d", pv);

        //afficher le score
        textprintf_ex(page, font, 10, 40, makecol(200, 0, 200), -1, "%d", score);

        //afficher le numero de la vague
        textprintf_ex(page, font, 10, 70, makecol(200, 0, 200), -1, "%de", vague);

        //on verifie si il n'y a pas de vagues en cours
        if((verification_fin_vague(ennemis)==0)&&(ennemis->n==nbennemis)&&(pv>0)&&(vague<9))
        {
            //lancer la vague suivante
            textout_ex(page,font, "Play: Lancer la vague", 620, 70, makecol(200, 0, 200), -1);
        }

        //bouton continuer
        if(mouse_b&1 && mouse_x>670 && mouse_x<720 && mouse_y<50 &&(verification_fin_vague(ennemis)==0)&&(ennemis->n==nbennemis)&& vague<9)
        {
            //le nombre d'ennemis par vagues
            if(compteur>8)
                compteur=0;

            ennemis->n=8-compteur;
            compteur=compteur+4;
            vague++;
        }

        // continuer avec la touche entree
        if(key[KEY_ENTER]&& verification_fin_vague(ennemis)==0 && ennemis->n==nbennemis && vague<9)
        {
            //le nombre d'ennemis par vagues
            if(compteur>8)
                compteur=0;

            ennemis->n=8-compteur;
            compteur=compteur+4;
            vague++;
        }
        //si victoire alors
        if((vague==9)&&(pv>0)&&(verification_fin_vague(ennemis)==0)&&(ennemis->n==nbennemis))
        {
            draw_sprite(page,victoire,SCREEN_W/3,SCREEN_H/3);
            //textout_ex(page,font, "VICTOIRE!", SCREEN_W/2, SCREEN_H/2, makecol(0, 0 ,255), -10);

            if(mouse_b&1)
                fin=1;
        }
        //si defaite alors
        if((pv<=0)&&(verification_fin_vague(ennemis)==0)&&(ennemis->n==nbennemis))
        {
            //textout_ex(page,font, "GAME OVER", SCREEN_W/2, SCREEN_H/2, makecol(255, 0 ,0), -1);
            draw_sprite(page,defaite,SCREEN_W/3,SCREEN_H/3);
            if(mouse_b&1)
                fin=1;
        }
        //afficher le decor du niveau correspondant et les elements
        decor=affichage_decor(decor, decor1, decor2, decor3,vague);
        draw_sprite(decor,elements,0,0);
        draw_sprite(page,curseur,mouse_x,mouse_y);

        // bouger tout le monde
        actualiserListeEnnemis(ennemis);
        actualiserDefense(vaisseau,acteurs);
        actualiserListeActeurs(acteurs);

        // de manière probabiliste (par défaut)
        if (rand()%300 < prob)
            ajouterEnnemi(ennemis,vague);

        // gérer les collisions
        collisionListeActeurs(ennemis,acteurs);

        // afficher tout le monde
        dessinerDefense(page,vaisseau);
        dessinerListeActeurs(page,acteurs);
        dessinerListeEnnemis(page,ennemis);

        // trajet des ennemis
        depListeEnnemis(chemin,ennemis,vague);

        //sortie avec touche echap
        if(key[KEY_ESC])
            fin = 1;

        // sortie avec la souris
        if(mouse_b&1 && mouse_x > 720 && mouse_y < 50)
            fin = 1;

        // afficher tout ça à l'écran
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // petite temporisation
        rest(10);
    }
    return 0;
}
END_OF_MAIN();
