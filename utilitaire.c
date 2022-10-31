#include <stdlib.h>
#include "utilitaire.h"

// Chargement "s�curis�" d'une image :
// interrompt le programme avec un message si probl�me...
BITMAP * load_bitmap_check(char *nomImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}
