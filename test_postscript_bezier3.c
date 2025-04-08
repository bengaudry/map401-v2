#include <stdio.h>
#include <stdlib.h>
#include "simplification_contours.h"
#include "postscript.h"

/* Arg1: fichier.pbm ; Arg2: fichier.eps ; Arg3: mode stroke ou fill ; Arg4: distance-seuil */
int main(int argc, char **argv){
    int nb_contours, nb_seg_init, nb_seg_simpl;
    Cellule_Liste_Liste_Point *Cel_init;
    Cellule_Liste_Liste_Bezier3 *Cel_simpl;
    double d = atoi(argv[4]);
    Image I = lire_fichier_image(argv[1]);

    Liste_Contour LC = calcul_contours_multiples(I);
    Liste_Contour_Bezier3 LCB3 = simplification_bezier3(LC, d);

    sortie_format_postcript_bezier3(argv[2], LCB3, I, argv[3]);

    /* Statistiques des contours initiaux et simplifiés */
    nb_contours = LC.taille;
    nb_seg_init = 0;
    nb_seg_simpl = 0;

    Cel_init = LC.first;
    Cel_simpl = LCB3.first;
    while (Cel_init != NULL) {
        nb_seg_init += Cel_init->liste.taille-1;
        nb_seg_simpl += Cel_simpl->data.taille;
        Cel_init = Cel_init->suiv;
        Cel_simpl = Cel_simpl->suiv;
    }

    /* Affichage des stats */
    printf("\nNombre de contours: %d\n", nb_contours);
    printf("Nombre de segments initiaux: %d\n", nb_seg_init);
    printf("Nombre de courbes bezier3: %d\n\n", nb_seg_simpl);

    return 0;
}
