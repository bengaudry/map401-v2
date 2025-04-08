#include <stdio.h>
#include "simplification_bezier.h"
#include "contour.h"
#include "bezier.h"

int main() {
    Contour C;
    Tableau_Point T;
    Bezier3 B3;
    int n;


    printf("===== TEST A =====\n");
    C = creer_liste_Point_vide();
    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(-2, -2));

    T = sequence_points_liste_vers_tableau(C);
    B3 = approx_bezier3(T, 0, 1);
    supprimer_liste_Point(C);
    afficher_bezier3(B3);

    printf("===== TEST B - Bezier 2 =====\n");
    C = creer_liste_Point_vide();

    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(-2, -2));
    C = ajouter_element_liste_Point(C, set_point(4, 5));

    T = sequence_points_liste_vers_tableau(C);
    B3 = approx_bezier3(T, 0, 2);
    supprimer_liste_Point(C);
    afficher_bezier3(B3);

    printf("===== TEST C - Bezier 2 =====\n");
    C = creer_liste_Point_vide();
    B3.c0 = set_point(0, 2);
    B3.c1 = set_point(0, 9);
    B3.c2 = set_point(2, 5);
    B3.c3 = set_point(4, 2);

    n = 4;
    C = ajouter_element_liste_Point(C, calcul_point_bezier3(B3, (double)0/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier3(B3, (double)1/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier3(B3, (double)2/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier3(B3, (double)3/n));
    C = ajouter_element_liste_Point(C, calcul_point_bezier3(B3, (double)4/n));

    T = sequence_points_liste_vers_tableau(C);

    printf("Courbe de bézier originale: \n");
    afficher_bezier3(B3);
    printf("Courbe de bézier approximative: \n");
    afficher_bezier3(approx_bezier3(T, 0, 4));

    supprimer_liste_Point(C);

    printf("===== TEST D =====\n");
    C = creer_liste_Point_vide();
    B3.c0 = set_point(0, 0);
    B3.c1 = set_point(1.737287, 0.929380);
    B3.c2 = set_point(1.844176, 3.489158);
    B3.c3 = set_point(5, 3);

    C = ajouter_element_liste_Point(C, set_point(0, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 1));
    C = ajouter_element_liste_Point(C, set_point(1, 2));
    C = ajouter_element_liste_Point(C, set_point(2, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 3));
    C = ajouter_element_liste_Point(C, set_point(4, 3));
    C = ajouter_element_liste_Point(C, set_point(5, 3));

    T = sequence_points_liste_vers_tableau(C);
    printf("Courbe de bézier originale: \n");
    afficher_bezier3(B3);
    printf("Courbe de bézier approximative: \n");
    afficher_bezier3(approx_bezier3(T, 0, 8));

    supprimer_liste_Point(C);

    return 0;
}




