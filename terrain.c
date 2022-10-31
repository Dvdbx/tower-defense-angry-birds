#include "terrain.h"
#include "utilitaire.h"

BITMAP * affichage_decor(BITMAP*bmp, BITMAP*bmp1, BITMAP*bmp2, BITMAP*bmp3,int vague)
{
    if(vague>=0 && vague<4)
        bmp=bmp1;

    if(vague>=4 && vague<7)
        bmp=bmp2;

    if(vague>=7 && vague<9)
        bmp=bmp3;

    return bmp;
}

