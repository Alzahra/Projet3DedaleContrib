/* Auteur: Nicolas JANEY                  */
/* nicolas.janey@univ-fcomte.fr           */
/* Septembre 2005                         */
/* Module de dessin des axes              */
/* du repere courant                      */

#ifndef MODULEAXES
#define MODULEAXES

#include "ModuleMatriceVecteur.h"

struct repere {
  vecteur o;
  vecteur axex;
  vecteur axey;
  vecteur axez; } ;

extern struct repere repereIdentite;

void switchAffichagePlan(void) ;
void axes(void) ;
void axes(struct repere *r);

#endif
