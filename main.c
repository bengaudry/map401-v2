#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "contour.h"
#include "postscript.h"
#include "simplification_bezier.h"
#include "simplification_contours.h"

int main (int argc, char **argv) {
    Image I;
    Liste_Contour seq_contours, seq_contours_simple;
    Liste_Contour_Bezier2 seq_contours_bezier2;
    Liste_Contour_Bezier3 seq_contours_bezier3;
    
    if (argc != 2)
        fprintf(stderr, "Utilisation: %s <chemin_fichier_pbm>\n", argv[0]),
        exit(1);

    // Mode par défaut : fill
    char mode[10] = "fill";

    // Lecture du fichier image en entrée, et génération des noms en sortie
    I = lire_fichier_image(argv[1]);
    char *nom_sortie = extraire_nom_fichier(argv[1]);
    char nom_sortie_simple[50];
    strcpy(nom_sortie_simple, nom_sortie);
    strcat(nom_sortie_simple, "_simple");
    strcat(nom_sortie, ".eps");
    strcat(nom_sortie_simple, ".eps");

    printf("Image : %s (%dx%d)\n", nom_sortie, largeur_image(I), hauteur_image(I));

    // Lecture de la séquence de contours
    seq_contours = creer_liste_liste_Point_vide();
    seq_contours = calcul_contours_multiples(I);
    printf("%d contours initiaux\n", seq_contours.taille);

    // Affichage du menu de simplification
    printf("============ CHOIX DE LA SIMPLIFICATION ============\n");
    printf("(1) Simplification par segments\n");
    printf("(2) Simplification par courbes de Bézier de degré 2\n");
    printf("(3) Simplification par courbes de Bézier de degré 3\n");

    // Lecture du choix de l'utilisateur
    int choix = -1;
    do {
        printf("> ");
        scanf("%d", &choix);
    } while (choix < 1 || choix > 3);

    // Lecture de la distance seuil choisie par l'utilisateur
    printf("Choisir une distance seuil :\n");
    double d = -1.0;
    do {
        printf("> ");
        scanf("%lf", &d);
    } while (d < 0);

    switch (choix)
    {
        case 1:
            // Choix du mode de remplissage :
            printf("Choisir un mode de remplissage (stroke | fill) :\n");
            do {
                printf("> ");
                scanf("%9s", mode);
            } while (strcmp(mode, "fill") != 0 && strcmp(mode, "stroke") != 0);

            seq_contours_simple = simplification_mult_contours(seq_contours, d);
            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);               // export de l'image de base
            sortie_format_postcript_mult_contours(nom_sortie_simple, seq_contours_simple, I, mode); // export de l'image simplifiée
            break;
        case 2:
            seq_contours_bezier2 = simplification_bezier2(seq_contours, d);
            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);          // export de l'image de base
            sortie_format_postcript_bezier2(nom_sortie_simple, seq_contours_bezier2, I, mode); // export de l'image simplifiée
            break;
        case 3:
            seq_contours_bezier3 = simplification_bezier3(seq_contours, d);
            // Export au format eps
            sortie_format_postcript_mult_contours(nom_sortie, seq_contours, I, mode);          // export de l'image de base
            sortie_format_postcript_bezier3(nom_sortie_simple, seq_contours_bezier3, I, mode); // export de l'image simplifiée
            break;
        default: break; // n'arrive jamais
    }

    return 0;
}
