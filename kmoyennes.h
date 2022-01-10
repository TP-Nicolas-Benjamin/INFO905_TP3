#ifndef __KMOYENNES_H__
#define __KMOYENNES_H__


//Renvoie vraie quand l'image est foncée
bool is_dark(Color col);

//Transforme l'image en noir et blanc
void black_white_image( Image* im );

//Couleurs noir et blanc
Color black = {.r=0,   .g=0,  .b=0};
Color white = {.r=255, .g=255,.b=255};

#endif
