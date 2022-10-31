#include <stdio.h>
#include <stdlib.h>
#include "sauvergarde.h"
#include "utilitaire.h"
#include <string.h>

void sauv(int pv,int score,int vague)
{
    FILE*fp;
    //ouverture du fichier
    fp=fopen("fichier.txt","w");

    //test d'ouverture
    if(fp==NULL)
    {
        printf("open error\n");
    }
    else
    {
        fscanf(fp,"%d", &pv);
        fscanf(fp,"%d", &score);
        fscanf(fp,"%d", &vague);
    }
    fclose(fp);

}
