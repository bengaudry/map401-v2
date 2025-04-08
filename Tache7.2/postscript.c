#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postscript.h"

void sortie_format_postcript(char *nom_fichier, Tableau_Point T, Image I, char *mode) {
    FILE *f = fopen(nom_fichier, "w");
    int hauteur = hauteur_image(I);
    int largeur = largeur_image(I);

    /* en-tete */
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n\n", largeur, hauteur);

    /* corps de l'image */
    fprintf(f, "%lf %lf moveto\n", T.tab[0].x, hauteur-T.tab[0].y);
    for (int i=1; i < T.taille; i++) {
        fprintf(f, "%lf %lf lineto\n", T.tab[i].x, hauteur-T.tab[i].y);
    }
    fprintf(f, "%lf %lf lineto\n", T.tab[0].x, hauteur-T.tab[0].y);
    
    if (strcmp(mode, "fill") == 0) {
      fprintf(f, "fill\n\n");
    }
    else {
      fprintf(f, "0 0 0 setrgbcolor 0 setlinewidth\n");
      fprintf(f, "stroke\n\n");
    }
    
    fprintf(f, "showpage");

    fclose(f);
}

void sortie_format_postcript_mult_contours(char *nom_fichier, Liste_Contour L, Image I, char *mode) {
  FILE *f = fopen(nom_fichier, "w");
  int hauteur = hauteur_image(I);
  int largeur = largeur_image(I);
  Cellule_Liste_Liste_Point *cel = L.first;
  Liste_Point LP;
  Tableau_Point T;

  /* en-tete */
  fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n\n", largeur, hauteur);

  /* corps de l'image */
  while (cel != NULL) {
    LP = cel->liste;
    T = sequence_points_liste_vers_tableau(LP);

    fprintf(f, "%lf %lf moveto\n", T.tab[0].x, hauteur-T.tab[0].y);
    for (int i=1; i < T.taille; i++) {
        fprintf(f, "%lf %lf lineto\n", T.tab[i].x, hauteur-T.tab[i].y);
    }

    cel = cel->suiv;
  }

  if (strcmp(mode, "fill") == 0) {
    fprintf(f, "fill\n\n");
  }
  else {
    fprintf(f, "0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(f, "stroke\n\n");
  }
  
  fprintf(f, "showpage\n");

  fclose(f);

}

void sortie_format_postcript_bezier2(char *nom_fichier, Liste_Contour_Bezier2 LCB2, Image I, char *mode) {
  FILE *f = fopen(nom_fichier, "w");
  int hauteur = hauteur_image(I);
  int largeur = largeur_image(I);
  Cellule_Liste_Liste_Bezier2 *cel1 = LCB2.first;
  Cellule_Liste_Bezier2 *cel2;
  Bezier3 B3;

  /* en-tete */
  fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n\n", largeur, hauteur);

  /* corps de l'image */
  while (cel1 != NULL) {
    cel2 = cel1->data.first;
    B3 = bezier2_vers_bezier3(cel2->data);
    fprintf(f, "%lf %lf moveto\n", B3.c0.x, hauteur-B3.c0.y);
    while (cel2 != NULL) {
      B3 = bezier2_vers_bezier3(cel2->data);
      fprintf(f, "%lf %lf %lf %lf %lf %lf curveto\n", B3.c1.x, hauteur-B3.c1.y, B3.c2.x, hauteur-B3.c2.y, B3.c3.x, hauteur-B3.c3.y);
      cel2 = cel2->suiv;
    }
    cel1 = cel1->suiv;
  }

  if (strcmp(mode, "fill") == 0) {
    fprintf(f, "fill\n\n");
  }
  else {
    fprintf(f, "0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(f, "stroke\n\n");
  }
  
  fprintf(f, "showpage\n");

  fclose(f);

}


void sortie_format_postcript_bezier3(char *nom_fichier, Liste_Contour_Bezier3 LCB3, Image I, char *mode) {
  FILE *f = fopen(nom_fichier, "w");
  int hauteur = hauteur_image(I);
  int largeur = largeur_image(I);
  Cellule_Liste_Liste_Bezier3 *cel1 = LCB3.first;
  Cellule_Liste_Bezier3 *cel2;
  Bezier3 B3;

  /* en-tete */
  fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n\n", largeur, hauteur);

  /* corps de l'image */
  while (cel1 != NULL) {
    cel2 = cel1->data.first;
    B3 = cel2->data;
    fprintf(f, "%lf %lf moveto\n", B3.c0.x, hauteur-B3.c0.y);
    while (cel2 != NULL) {
      B3 = cel2->data;
      fprintf(f, "%lf %lf %lf %lf %lf %lf curveto\n", B3.c1.x, hauteur-B3.c1.y, B3.c2.x, hauteur-B3.c2.y, B3.c3.x, hauteur-B3.c3.y);
      cel2 = cel2->suiv;
    }
    cel1 = cel1->suiv;
  }

  if (strcmp(mode, "fill") == 0) {
    fprintf(f, "fill\n\n");
  }
  else {
    fprintf(f, "0 0 0 setrgbcolor 0 setlinewidth\n");
    fprintf(f, "stroke\n\n");
  }
  
  fprintf(f, "showpage\n");

  fclose(f);

}