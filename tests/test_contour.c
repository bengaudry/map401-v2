#include <stdlib.h>
#include <stdio.h>
#include "../contour.h"

int main(int argc, char **argv) {
    //Point pixel_depart;
    Image I = lire_fichier_image(argv[1]);

    //TEST trouver_pixel_depart
    /*
    printf("-- Affichage du terrain --\n");
    ecrire_image(I);
    pixel_depart = trouver_pixel_depart(I);
    printf("Pixel de départ trouvé (x,y) : %f,%f\n", pixel_depart.x, pixel_depart.y);
    */

    //TEST calcul_contour_image
    ecrire_image(I);
    calcul_contour_image(I);    

    return 0;
}






