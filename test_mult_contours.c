#include <stdio.h>
#include <stdlib.h>
#include "contour.h"
#include "image.h"
#include "geometrie.h"

int main(int argc, char **argv) {
    Image I = lire_fichier_image(argv[1]);
    Liste_Contour L;

    ecrire_image(I);
    
    L = calcul_contours_multiples(I);
    ecrire_liste_contour(L);
    
    return 0;
}